#include "FaceAnalyzer.h"

#include <opencv2/core/types.hpp>
#include <opencv2/opencv.hpp>
#include <libfacedetection/facedetectcnn.h>

#include "Utility/ImageUtility.h"

using namespace pricam;

Rect FaceAnalyzer::normalizeRect(const Rect&& _rect, const int _frameWidth, const int _frameHeight) const
{
	int x = _rect.X() < 0 ? 0 : _rect.X();
	int y = _rect.Y() < 0 ? 0 : _rect.Y();
	int w = _rect.W() < 0 ? 0 : _rect.W();
	int h = _rect.H() < 0 ? 0 : _rect.H();

	w = _rect.X() + w > _frameWidth ? _frameWidth - _rect.X() : w;
	h = _rect.Y() + h > _frameHeight ? _frameHeight - _rect.Y() : h;

	return {x, y, w, h};
}

std::vector<Rect> FaceAnalyzer::FindRects(const cv::Mat& _frame) const
{
	const std::unique_ptr<unsigned char> detectBuffer = std::unique_ptr<unsigned char>(new unsigned char[m_detectBufferSize]);
	int* resultCount = facedetect_cnn(detectBuffer.get(), const_cast<unsigned char*>(_frame.ptr(0)), _frame.cols, _frame.rows, (int)_frame.step);
	if (nullptr == resultCount)
		return {};
	std::vector<Rect> rects;
	for (int i = 0; i < *resultCount; i++)
	{
		const short* p = reinterpret_cast<short*>(resultCount + 1) + 142 * i;
		rects.emplace_back(normalizeRect(Rect(p[1], p[2], p[3], p[4]), _frame.cols, _frame.rows));
	}
	return rects;
}
