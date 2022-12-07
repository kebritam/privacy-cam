#ifndef PRIVACYCAM_FACE_ANALYZER_H
#define PRIVACYCAM_FACE_ANALYZER_H

#include <PreProcessors.h>
#include <vector>

namespace cv
{
	class Mat;
}

namespace pricam
{
	struct Rect;
	class PipelineElement;

	class FaceAnalyzer
	{
		const int m_detectBufferSize;

	public:
		DllExport FaceAnalyzer();
		[[nodiscard]] DllExport std::vector<Rect> FindRects(const cv::Mat& _frame) const;
	};
}

#endif // end of PRIVACYCAM_FACE_ANALYZER_H
