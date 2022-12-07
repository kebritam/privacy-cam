#ifndef PRIVACYCAM_IMAGE_UTILITY_H
#define PRIVACYCAM_IMAGE_UTILITY_H

#include <PreProcessors.h>
#include <vector>

namespace cv
{
	class Mat;
}

namespace pricam
{
	class Rect
	{
		int m_x, m_y, m_w, m_h;
	public:
		DllExport Rect(const Rect& _other);
		DllExport Rect(Rect&& _other) noexcept;
		DllExport Rect& operator=(const Rect& _other);
		DllExport Rect& operator=(Rect&& _other) noexcept;

		DllExport Rect(int _x, int _y, int _w, int _h);
		DllExport ~Rect();

		DllExport int X() const;
		DllExport int Y() const;
		DllExport int W() const;
		DllExport int H() const;
	};

	struct ImageUtility
	{
		ImageUtility(const ImageUtility& _other) = delete;
		ImageUtility(ImageUtility&& _other) noexcept = delete;
		ImageUtility& operator=(const ImageUtility& _other) = delete;
		ImageUtility& operator=(ImageUtility&& _other) noexcept = delete;

		ImageUtility() = delete;
		DllExport ~ImageUtility();
		DllExport static void BlurRects(const cv::Mat& _image, const std::vector<Rect>& _rects);
		DllExport static void BlurRect(const cv::Mat& _image, const Rect& _rect);
	};
} // namespace pricam

#endif // end of PRIVACYCAM_IMAGE_UTILITY_H
