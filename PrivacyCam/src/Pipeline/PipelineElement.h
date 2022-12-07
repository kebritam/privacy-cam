#ifndef PRIVACYCAM_PIPELINE_ELEMENT_H
#define PRIVACYCAM_PIPELINE_ELEMENT_H

#include <memory>
#include <PreProcessors.h>
#include <vector>

namespace cv
{
	class Mat;
}

namespace pricam
{
	class Rect;

	class PipelineElement
	{
		std::unique_ptr<cv::Mat> m_frame;
		std::vector<Rect> m_rects;

	public:
		PipelineElement(const PipelineElement&) = delete;
		PipelineElement& operator= (const PipelineElement&) = delete;
		PipelineElement(const PipelineElement&&) = delete;
		PipelineElement& operator= (const PipelineElement&&) = delete;

		DllExport ~PipelineElement();
		DllExport PipelineElement();
		DllExport explicit PipelineElement(const cv::Mat& _frame);
		DllExport PipelineElement(const cv::Mat& _frame, const std::vector<Rect>& _rects);

		DllExport void FillFrame(const cv::Mat& _frame) const;
		DllExport [[nodiscard]] cv::Mat GetFrame() const;
		DllExport [[nodiscard]] Rect GetRect(size_t _idx) const;
		DllExport [[nodiscard]] bool NoDetection() const;
		DllExport [[nodiscard]] std::vector<Rect> GetRects();
		DllExport void FillRects(const std::vector<Rect>& _rects);
		DllExport void AddRect(const Rect& _rect);
		DllExport [[nodiscard]] bool IsEmpty() const;
	};
}

#endif // end of PRIVACYCAM_PIPELINE_ELEMENT_H
