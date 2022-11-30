#include "PipelineElement.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core/types.hpp>

using namespace pricam;

PipelineElement::~PipelineElement() = default;

PipelineElement::PipelineElement() :
	PipelineElement(cv::Mat())
{
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

void PipelineElement::FillFrame(const cv::Mat& _frame) const
{
	_frame.copyTo(*m_frame);
}

cv::Mat PipelineElement::GetFrame() const
{
	return m_frame->clone();
}

cv::Rect PipelineElement::GetRect(const size_t _idx)
{
	if (_idx >= m_rects.size())
		throw std::runtime_error(
			"there are " + std::to_string(m_rects.size()) +
			" rects and the caller asked for index " + std::to_string(_idx));
	return m_rects.at(_idx);
}

bool PipelineElement::NoDetection() const
{
	return m_rects.empty();
}