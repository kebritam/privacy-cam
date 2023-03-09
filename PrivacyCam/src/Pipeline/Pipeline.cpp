#include "Pipeline.h"

#include "Analyzer/FaceAnalyzer.h"
#include "opencv2/opencv.hpp" // TODO: do not expose opencv to pipeline

#include "Utility/ThreadPool.h"

#include "Pipeline/PipelineElement.h"
#include "ImageGrabber/ImageGrabber.h"
#include "ImageGrabber/ImageGrabberVideo.h"
#include "Setting/Setting.h"
#include "Utility/ImageUtility.h"
#include "Utility/Logger.h"
#include "Utility/ScopedTimer.h"
#include "Utility/UniversalTimer.h"

using namespace pricam;

Pipeline::Pipeline(const Setting& _setting) :
	m_threadPool(std::make_unique<BS::thread_pool>(_setting.ThreadPoolSize)),
	m_faceAnalyzer(std::make_unique<FaceAnalyzer>()),
	m_isPipelineStopped(true),
	m_pipeDuration(0), m_grabFrameDuration(0), m_detectFacesDuration(0), m_detectPlatesDuration(0), m_blurDuration(0), m_saveFrameDuration(0)
{
	if (StreamType::VIDEO == _setting.Stream)
		m_imageGrabber = std::make_unique<ImageGrabberVideo>(_setting.Video);
	else
		throw std::runtime_error("StreamType is not supported!");
}

Pipeline::~Pipeline() = default;

void Pipeline::Run()
{
	m_isPipelineStopped = false;

	std::unique_ptr<PipelineElement> grabElement = std::make_unique<PipelineElement>();
	std::unique_ptr<PipelineElement> detectFaceElement = std::make_unique<PipelineElement>();
	std::unique_ptr<PipelineElement> detectPlateElement = std::make_unique<PipelineElement>();
	std::unique_ptr<PipelineElement> blurElement = std::make_unique<PipelineElement>();
	std::unique_ptr<PipelineElement> saveElement = std::make_unique<PipelineElement>();

	while (false == m_isPipelineStopped)
	{
		ScopedTimer pipeTimer(&m_pipeDuration);
		std::future<std::unique_ptr<PipelineElement>> generateEmptyElementFuture = m_threadPool->submit(
			[]()
			{
				return std::make_unique<PipelineElement>();
			}
		);
		std::future<std::unique_ptr<PipelineElement>> grabFrameFuture = m_threadPool->submit(
			[this, &grabElement]()
			{
				return grabFrame(std::move(grabElement));
			}
		);
		std::future<std::unique_ptr<PipelineElement>> detectFacesFuture = m_threadPool->submit(
			[this, &detectFaceElement]()
			{
				return detectFaces(std::move(detectFaceElement));
			}
		);
		std::future<std::unique_ptr<PipelineElement>> detectPlatesFuture = m_threadPool->submit(
			[this, &detectPlateElement]()
			{
				return detectPlates(std::move(detectPlateElement));
			}
		);
		std::future<std::unique_ptr<PipelineElement>> blurFuture = m_threadPool->submit(
			[this, &blurElement]()
			{
				return blur(std::move(blurElement));
			}
		);
		std::future<std::unique_ptr<PipelineElement>> saveFuture = m_threadPool->submit(
			[this, &saveElement]()
			{
				return saveFrame(std::move(saveElement));
			}
		);

		auto tempPipeElement = saveFuture.get();
		saveElement = blurFuture.get();
		blurElement = detectPlatesFuture.get();
		detectPlateElement = detectFacesFuture.get();
		detectFaceElement = grabFrameFuture.get();
		grabElement = generateEmptyElementFuture.get();

		pipeTimer.EndTimer();
		processPipes();
		optForFinishing();
	}
}

std::unique_ptr<PipelineElement> Pipeline::grabFrame(std::unique_ptr<PipelineElement> _pipelineElement)
{
	std::string detec("grab");
	TimerHandle handle = m_universalTiming.StartTimer(detec);
	ScopedTimer timer(&m_grabFrameDuration);
	try
	{
		const cv::Mat frame = m_imageGrabber->GetNewFrame();
		if (m_imageGrabber->GetGrabState() == GrabState::ONGOING)
		{
			_pipelineElement->FillFrame(frame);
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	m_universalTiming.EndTimer(handle);
	return _pipelineElement;
}

std::unique_ptr<PipelineElement> Pipeline::detectFaces(std::unique_ptr<PipelineElement> _pipelineElement)
{
	std::string detec("detect");
	TimerHandle handle = m_universalTiming.StartTimer(detec);
	ScopedTimer timer(&m_detectFacesDuration);
	try
	{
		if (_pipelineElement->IsEmpty())
			return _pipelineElement;
		const std::vector<Rect> rects = m_faceAnalyzer->FindRects(_pipelineElement->GetFrame());
		_pipelineElement->FillRects(rects);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	m_universalTiming.EndTimer(handle);
	return _pipelineElement;
}

std::unique_ptr<PipelineElement> Pipeline::detectPlates(std::unique_ptr<PipelineElement> _pipelineElement)
{
	ScopedTimer timer(&m_detectPlatesDuration);
	if (_pipelineElement->IsEmpty())
		return _pipelineElement;
	return _pipelineElement;
	// TODO: here
}
std::unique_ptr<PipelineElement> Pipeline::blur(std::unique_ptr<PipelineElement> _pipelineElement)
{
	ScopedTimer timer(&m_blurDuration);
	try
	{
		if (_pipelineElement->IsEmpty())
			return _pipelineElement;
		ImageUtility::BlurRects(_pipelineElement->GetFrame(), _pipelineElement->GetRects());
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return _pipelineElement;
}
std::unique_ptr<PipelineElement> Pipeline::saveFrame(std::unique_ptr<PipelineElement> _pipelineElement)
{
	ScopedTimer timer(&m_saveFrameDuration);
	try
	{
		if (_pipelineElement->IsEmpty())
			return _pipelineElement;
		m_imageGrabber->SaveFrame(_pipelineElement->GetFrame());
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return _pipelineElement;
}

void Pipeline::optForFinishing()
{
	if (m_imageGrabber->GetGrabState() == GrabState::ENDED)
	{
		m_isPipelineStopped = true;
	}
}

void Pipeline::processPipes() const
{
	LOG_INFO("Whole pipeline took {} seconds.", m_pipeDuration);
	LOG_INFO("Grabbing frametook {} seconds.", m_grabFrameDuration);
	LOG_INFO("Detecting faces took {} seconds.", m_detectFacesDuration);
	LOG_INFO("Detecting plates took {} seconds.", m_detectPlatesDuration);
	LOG_INFO("Bluring detections took {} seconds.", m_blurDuration);
	LOG_INFO("Saving frame took {} seconds.", m_saveFrameDuration);
}
