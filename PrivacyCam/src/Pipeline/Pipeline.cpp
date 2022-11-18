#include "Pipeline.h"

#include <Utility/ThreadPool.h>
#include <ImageGrabber/ImageGrabber.h>
#include <Setting/Setting.h>

using namespace pricam;

Pipeline::Pipeline(const Setting& _setting) :
	m_isPipelineStopped(true),
	m_threadPool(std::make_unique<ThreadPool>(4))
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
	while (false == m_isPipelineStopped)
	{
		std::future<std::shared_ptr<PipelineElement>> grabFrameFuture = m_threadPool->Push(
			[this](int) { 
				return grabFrame(); 
			}
		);
		std::future<std::shared_ptr<PipelineElement>> detectFacesFuture = m_threadPool->Push(
			[this](int) {
				return detectFaces(std::make_shared<PipelineElement>()); // TODO: this
			}
		);
		std::future<std::shared_ptr<PipelineElement>> detectPlatesFuture = m_threadPool->Push(
			[this](int) {
				return detectPlates(std::make_shared<PipelineElement>()); // TODO: this
			}
		);
		std::future<std::shared_ptr<PipelineElement>> blurFuture = m_threadPool->Push(
			[this](int) {
				return blur(std::make_shared<PipelineElement>()); // TODO: this
			}
		);

		auto grabRes = grabFrameFuture.get();
		auto detecFacetRes = detectFacesFuture.get();
		auto detecPlatetRes = detectPlatesFuture.get();
		auto blurRes = blurFuture.get();

		processPipes();
	}
}

PipelineElement::PipelineElement(const cv::Mat& _frame) :
	PipelineElement(_frame, std::vector<cv::Rect>())
{
}

PipelineElement::PipelineElement(const cv::Mat& _frame, const std::vector<cv::Rect>& _rects) :
	m_frame(std::make_unique<cv::Mat>(_frame)),
	m_rects(_rects)
{
}

std::shared_ptr<PipelineElement> Pipeline::grabFrame()
{
	return std::make_shared<PipelineElement>(m_imageGrabber->GetNewFrame());
}

std::shared_ptr<PipelineElement> detectFaces(const std::shared_ptr<PipelineElement>& _pipelineElement)
{
	// TODO: here
}

std::shared_ptr<PipelineElement> detectPlates(const std::shared_ptr<PipelineElement>& _pipelineElement)
{
	// TODO: here
}
std::shared_ptr<PipelineElement> blur(const std::shared_ptr<PipelineElement>& _pipelineElement)
{
	// TODO: here
}
std::shared_ptr<PipelineElement> saveFrame(const std::shared_ptr<PipelineElement>& _pipelineElement)
{
	// TODO: here
}

void processPipes()
{
	// TODO: here
}

cv::Mat PipelineElement::GetFrame()
{
	return m_frame->clone();
}

cv::Rect PipelineElement::GetRect(int idx)
{
	if (idx >= m_rects.size())
		throw std::runtime_error(
			"there are " + std::to_string(m_rects.size()) +
			" rects and the caller asked for index " + std::to_string(idx));
	return m_rects.at(idx);
}
