#ifndef PRIVACYCAM_IMAGE_GRABBER_H
#define PRIVACYCAM_IMAGE_GRABBER_H

#include "PreProcessors.h"

namespace cv
{
	class Mat;
}

namespace pricam
{
	enum class GrabState
	{
		NONE,
		NOT_STARTED,
		ONGOING,
		ENDED,
	};

	class ImageGrabber
	{
	protected:
		GrabState m_grabState;
	public:
		ImageGrabber(const ImageGrabber& _other) = delete;
		ImageGrabber(ImageGrabber&& _other) noexcept = delete;
		ImageGrabber& operator=(const ImageGrabber& _other) = delete;
		ImageGrabber& operator=(ImageGrabber&& _other) noexcept = delete;

		DllExport ImageGrabber();
		DllExport virtual ~ImageGrabber() = 0;

		DllExport virtual cv::Mat GetNewFrame() = 0;
		DllExport virtual void SaveFrame(const cv::Mat& _saveImage) = 0;

		DllExport GrabState GetGrabState() const;
		DllExport void SetGrabState(GrabState _grabState);
	};
}

#endif // end of PRIVACYCAM_IMAGE_GRABBER_H
