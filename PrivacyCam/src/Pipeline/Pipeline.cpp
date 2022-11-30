#include "Pipeline.h"

#include <opencv2/opencv.hpp> // TODO: do not expose opencv to pipeline

#include <Utility/ThreadPool.h>

#include <Pipeline/PipelineElement.h>
#include <ImageGrabber/ImageGrabber.h>
#include <Setting/Setting.h>

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
	std::vector<std::unique_ptr<PipelineElement>> pipelineElements;
	while (false == m_isPipelineStopped)
	{
		std::future<std::unique_ptr<PipelineElement>> generateNewElementFuture = m_threadPool->Push(
			[this](int) {
				return generateEmptyElement();
			}
		);
		std::future<std::unique_ptr<PipelineElement>> grabFrameFuture = m_threadPool->Push(
			[this, &pipelineElements](int) { 
				return grabFrame(std::move(pipelineElements[0]));
			}
		);
		std::future<std::unique_ptr<PipelineElement>> detectFacesFuture = m_threadPool->Push(
			[this, &pipelineElements](int) {
				return detectFaces(std::move(pipelineElements[1]));
			}
		);
		std::future<std::unique_ptr<PipelineElement>> detectPlatesFuture = m_threadPool->Push(
			[this, &pipelineElements](int) {
				return detectPlates(std::move(pipelineElements[2]));
			}
		);
		std::future<std::unique_ptr<PipelineElement>> blurFuture = m_threadPool->Push(
			[this, &pipelineElements](int) {
				return blur(std::move(pipelineElements[3]));
			}
		);
		std::future<std::unique_ptr<PipelineElement>> saveFuture = m_threadPool->Push(
			[this, &pipelineElements](int) {
				return saveFrame(std::move(pipelineElements[4]));
			}
		);

		pipelineElements.push_back(generateNewElementFuture.get());
		pipelineElements.push_back(grabFrameFuture.get());
		pipelineElements.push_back(detectFacesFuture.get());
		pipelineElements.push_back(detectPlatesFuture.get());
		pipelineElements.push_back(blurFuture.get());
		pipelineElements.push_back(saveFuture.get());

		processPipes(pipelineElements);

		pipelineElements.clear();
	}
}

std::unique_ptr<PipelineElement> Pipeline::generateEmptyElement()
{
	return { };
}

std::unique_ptr<PipelineElement> Pipeline::grabFrame(std::unique_ptr<PipelineElement>&& _pipelineElement) const
{
	_pipelineElement->FillFrame(m_imageGrabber->GetNewFrame());
	return _pipelineElement;
}

std::unique_ptr<PipelineElement> Pipeline::detectFaces(std::unique_ptr<PipelineElement>&& _pipelineElement)
{
	if (_pipelineElement->GetFrame().empty())
		return _pipelineElement;
	// TODO: here
}

std::unique_ptr<PipelineElement> Pipeline::detectPlates(std::unique_ptr<PipelineElement>&& _pipelineElement)
{
	if (_pipelineElement->GetFrame().empty())
		return _pipelineElement;
	// TODO: here
}
std::unique_ptr<PipelineElement> Pipeline::blur(std::unique_ptr<PipelineElement>&& _pipelineElement)
{
	if (_pipelineElement->NoDetection())
		return _pipelineElement;

	// TODO: here
}
std::unique_ptr<PipelineElement> Pipeline::saveFrame(std::unique_ptr<PipelineElement>&& _pipelineElement)
{
	if (_pipelineElement->GetFrame().empty())
		return _pipelineElement;
	// TODO: here
}

void Pipeline::processPipes(const std::vector<std::unique_ptr<PipelineElement>>& _elements)
{
	// TODO: here
}
