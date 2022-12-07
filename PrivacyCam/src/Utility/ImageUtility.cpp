#include "ImageUtility.h"

#include "opencv2/opencv.hpp"
#include "opencv2/core/types.hpp"

using namespace pricam;

Rect::Rect(const int _x, const int _y, const int _w, const int _h) :
	m_x(_x < 0 ? 0 : _x),
	m_y(_y < 0 ? 0 : _y),
	m_w(_w < 0 ? 0 : _w),
	m_h(_h < 0 ? 0 : _h)
{
}

Rect::~Rect() = default;

Rect::Rect(const Rect& _other) = default;

Rect::Rect(Rect&& _other) noexcept
	: m_x(_other.m_x),
	m_y(_other.m_y),
	m_w(_other.m_w),
	m_h(_other.m_h)
{
}

Rect& Rect::operator=(const Rect& _other)
{
	if (this == &_other)
		return *this;
	m_x = _other.m_x;
	m_y = _other.m_y;
	m_w = _other.m_w;
	m_h = _other.m_h;
	return *this;
}

Rect& Rect::operator=(Rect&& _other) noexcept
{
	if (this == &_other)
		return *this;
	m_x = _other.m_x;
	m_y = _other.m_y;
	m_w = _other.m_w;
	m_h = _other.m_h;
	return *this;
}

int Rect::X() const
{
	return m_x;
}

int Rect::Y() const
{
	return m_y;
}

int Rect::W() const
{
	return m_w;
}

int Rect::H() const
{
	return m_h;
}

ImageUtility::~ImageUtility() = default;

void ImageUtility::BlurRect(const cv::Mat& _image, const Rect& _rect)
{

	const cv::Rect rect(_rect.X(), _rect.Y(), _rect.W(), _rect.H());
	cv::GaussianBlur(_image(rect), _image(rect), cv::Size(51, 51), 0);

}

void ImageUtility::BlurRects(const cv::Mat& _image, const std::vector<Rect>& _rects)
{
	for (const auto& rect : _rects)
	{
		ImageUtility::BlurRect(_image, rect);
	}
}

