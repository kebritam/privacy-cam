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
	class ImageGrabberVideo final : public ImageGrabber
	{
		std::string m_videoFilePath;
		std::unique_ptr<cv::VideoCapture> m_videoCapture;
	public:
		DllExport explicit ImageGrabberVideo(const std::string& _videoPath);
		DllExport cv::Mat GetNewFrame() override;
	};
}

#endif // end of PRIVACYCAM_IMAGE_GRABBER_VIDEO_H
