#include "Pipeline.h"

#include "opencv2/opencv.hpp" // TODO: do not expose opencv to pipeline

#include "Utility/ThreadPool.h"

#include "Pipeline/PipelineElement.h"
#include "ImageGrabber/ImageGrabber.h"
#include "ImageGrabber/ImageGrabberVideo.h"
#include "Setting/Setting.h"

using namespace pricam;

Pipeline::Pipeline(const Setting& _setting) :
	m_threadPool(std::make_unique<ThreadPool>(4)),
	m_isPipelineStopped(true)
{
	if (StreamType::VIDEO == _setting.Stream)
		m_imageGrabber = std::make_unique<ImageGrabberVideo>(_setting.Video.InputVideoLocation);
	else
		throw std::runtime_error("StreamType is not supported!");
}

Pipeline::~Pipeline() = default;

void Pipeline::Run()
{
	m_isPipelineStopped = false;

	std::unique_ptr<PipelineElement> pipelineElement1 = std::make_unique<PipelineElement>();
	std::unique_ptr<PipelineElement> pipelineElement2 = std::make_unique<PipelineElement>();
	std::unique_ptr<PipelineElement> pipelineElement3 = std::make_unique<PipelineElement>();
	std::unique_ptr<PipelineElement> pipelineElement4 = std::make_unique<PipelineElement>();
	std::unique_ptr<PipelineElement> pipelineElement5 = std::make_unique<PipelineElement>();

	while (false == m_isPipelineStopped)
	{
		std::future<std::unique_ptr<PipelineElement>> grabFrameFuture = m_threadPool->Push(
			[this, &pipelineElement1](int)
			{
				return grabFrame(std::move(pipelineElement1));
			}
		);
		std::future<std::unique_ptr<PipelineElement>> detectFacesFuture = m_threadPool->Push(
			[this, &pipelineElement2](int)
			{
				return detectFaces(std::move(pipelineElement2));
			}
		);
		std::future<std::unique_ptr<PipelineElement>> detectPlatesFuture = m_threadPool->Push(
			[this, &pipelineElement3](int)
			{
				return detectPlates(std::move(pipelineElement3));
			}
		);
		std::future<std::unique_ptr<PipelineElement>> blurFuture = m_threadPool->Push(
			[this, &pipelineElement4](int)
			{
				return blur(std::move(pipelineElement4));
			}
		);
		std::future<std::unique_ptr<PipelineElement>> saveFuture = m_threadPool->Push(
			[this, &pipelineElement5](int)
			{
				return saveFrame(std::move(pipelineElement5));
			}
		);

		auto tempPipeElement = saveFuture.get();
		pipelineElement5 = blurFuture.get();
		pipelineElement4 = detectPlatesFuture.get();
		pipelineElement3 = detectFacesFuture.get();
		pipelineElement2 = grabFrameFuture.get();

		// std::vector<std::unique_ptr<PipelineElement>> elemnts;
		// elemnts.push_back(grabFrameFuture.get());
		// elemnts.push_back(detectFacesFuture.get());
		// elemnts.push_back(detectPlatesFuture.get());
		// elemnts.push_back(blurFuture.get());
		// elemnts.push_back(saveFuture.get());
		// processPipes(elemnts);

	}
}

std::unique_ptr<PipelineElement> Pipeline::grabFrame(std::unique_ptr<PipelineElement>&& _pipelineElement) const
{
	_pipelineElement->FillFrame(m_imageGrabber->GetNewFrame());
	return _pipelineElement;
}

std::unique_ptr<PipelineElement> Pipeline::detectFaces(std::unique_ptr<PipelineElement>&& _pipelineElement)
{
	if (_pipelineElement->IsEmpty())
		return _pipelineElement;
	// TODO: here
}

std::unique_ptr<PipelineElement> Pipeline::detectPlates(std::unique_ptr<PipelineElement>&& _pipelineElement)
{
	if (_pipelineElement->IsEmpty())
		return _pipelineElement;
	// TODO: here
}
std::unique_ptr<PipelineElement> Pipeline::blur(std::unique_ptr<PipelineElement>&& _pipelineElement)
{
	if (_pipelineElement->IsEmpty())
		return _pipelineElement;

	// TODO: here
}
std::unique_ptr<PipelineElement> Pipeline::saveFrame(std::unique_ptr<PipelineElement>&& _pipelineElement)
{
	if (_pipelineElement->IsEmpty())
		return _pipelineElement;
	// TODO: here
}

void Pipeline::processPipes(std::vector<std::unique_ptr<PipelineElement>> _elements)
{
	for (size_t i=0 ; i<_elements.size()-1 ; i++)
	{
		*(_elements.end() - i) = std::move(*(_elements.end() - (i + 1)));
	}
}
