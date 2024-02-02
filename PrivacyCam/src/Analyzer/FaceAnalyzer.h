#ifndef PRIVACYCAM_FACE_ANALYZER_H
#define PRIVACYCAM_FACE_ANALYZER_H

#include <vector>

#include "PreProcessors.h"

namespace cv
{
	class Mat;
}

namespace pricam
{
	class Rect;
	class PipelineElement;

	class FaceAnalyzer
	{
		constexpr static int m_detectBufferSize = 0x20000;

		[[nodiscard]] Rect normalizeRect(const Rect&& _rect, int _frameWidth, int _frameHeight) const;
	public:
		[[nodiscard]] DllExport std::vector<Rect> FindRects(const cv::Mat& _frame) const;
	};
}

#endif // end of PRIVACYCAM_FACE_ANALYZER_H
