#ifndef PRIVACYCAM_IMAGE_GRABBER_H
#define PRIVACYCAM_IMAGE_GRABBER_H

#include <PreProcessors.h>

namespace cv
{
	class Mat;
}

namespace pricam
{
	class ImageGrabber
	{
	public:
		ImageGrabber(const ImageGrabber& _other) = delete;
		ImageGrabber(ImageGrabber&& _other) noexcept = delete;
		ImageGrabber& operator=(const ImageGrabber& _other) = delete;
		ImageGrabber& operator=(ImageGrabber&& _other) noexcept = delete;

		DllExport ImageGrabber();
		DllExport virtual ~ImageGrabber();
		DllExport virtual cv::Mat GetNewFrame() = 0;
	};
}

#endif // end of PRIVACYCAM_IMAGE_GRABBER_H
