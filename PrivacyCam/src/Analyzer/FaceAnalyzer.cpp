#include "FaceAnalyzer.h"

#include "opencv2/core/types.hpp"
#include "opencv2/opencv.hpp"
#include "libfacedetection/facedetectcnn.h"

#include "Utility/ImageUtility.h"

using namespace pricam;

FaceAnalyzer::FaceAnalyzer() :
	m_detectBufferSize(0x20000)
{
}

std::vector<Rect> FaceAnalyzer::FindRects(const cv::Mat& _frame) const
{
	const std::unique_ptr<unsigned char> detectBuffer = std::unique_ptr<unsigned char>(new unsigned char[m_detectBufferSize]);
	int* resultCount = facedetect_cnn(detectBuffer.get(), (unsigned char*)(_frame.ptr(0)), _frame.cols, _frame.rows, (int)_frame.step);
	if (nullptr == resultCount)
		return {};
	std::vector<Rect> rects;
	for (int i = 0; i < *resultCount; i++)
	{
		const short* p = ((short*)(resultCount + 1)) + 142 * i;
		rects.emplace_back(Rect(p[1], p[2], p[3], p[4]));
	}
	return rects;
}
