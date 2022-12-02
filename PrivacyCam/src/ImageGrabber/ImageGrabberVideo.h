#ifndef PRIVACYCAM_IMAGE_GRABBER_VIDEO_H
#define PRIVACYCAM_IMAGE_GRABBER_VIDEO_H

#include <memory>
#include <PreProcessors.h>
#include <string>

#include "ImageGrabber.h"

namespace cv
{
	class VideoCapture;
	class Mat;
}

namespace pricam
{
	class ImageGrabberVideo : public ImageGrabber
	{
		std::string m_videoFilePath;
		std::unique_ptr<cv::VideoCapture> m_videoCapture;
	public:
		ImageGrabberVideo(const ImageGrabberVideo& _other) = delete;
		ImageGrabberVideo(ImageGrabberVideo&& _other) noexcept = delete;
		ImageGrabberVideo& operator=(const ImageGrabberVideo& _other) = delete;
		ImageGrabberVideo& operator=(ImageGrabberVideo&& _other) noexcept = delete;

		DllExport explicit ImageGrabberVideo(const std::string& _videoPath);
		DllExport ~ImageGrabberVideo() override;
		DllExport cv::Mat GetNewFrame() override;
	};
}

#endif // end of PRIVACYCAM_IMAGE_GRABBER_VIDEO_H
