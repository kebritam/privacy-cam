#ifndef PRIVACYCAM_PIPELINE_ELEMENT_H
#define PRIVACYCAM_PIPELINE_ELEMENT_H

#include <opencv2/core/types.hpp>

namespace pricam
{

	class PipelineElement
	{
		std::unique_ptr<cv::Mat> m_frame;
		std::vector<cv::Rect> m_rects;

	public:
		PipelineElement(const PipelineElement&) = delete;
		PipelineElement& operator= (const PipelineElement&) = delete;
		PipelineElement(const PipelineElement&&) = delete;
		PipelineElement& operator= (const PipelineElement&&) = delete;

		~PipelineElement();
		PipelineElement();
		explicit PipelineElement(const cv::Mat& _frame);
		PipelineElement(const cv::Mat& _frame, const std::vector<cv::Rect>& _rects);

		void FillFrame(const cv::Mat& _frame) const;
		[[nodiscard]] cv::Mat GetFrame() const;
		cv::Rect GetRect(size_t _idx);
		[[nodiscard]] bool NoDetection() const;

		[[nodiscard]] bool IsEmpty() const;
	};
}

#endif // end of PRIVACYCAM_PIPELINE_ELEMENT_H
