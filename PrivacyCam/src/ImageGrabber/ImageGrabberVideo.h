#ifndef PRIVACYCAM_IMAGE_GRABBER_VIDEO_H
#define PRIVACYCAM_IMAGE_GRABBER_VIDEO_H

#include <memory>
#include <string>

#include "PreProcessors.h"
#include "ImageGrabber.h"

namespace cv
{
	class VideoWriter;
	class VideoCapture;
	class Mat;
}

namespace pricam
{
	struct VideoSetting;

	struct Size
	{
		int Width;
		int Height;
	};

	class ImageGrabberVideo : public ImageGrabber
	{
		std::string m_videoFilePath;
		double m_frameRate;
		Size m_frameSize;
		uint32_t m_videoFrameCount;
		uint32_t m_grabbedFrameCount;
		std::unique_ptr<cv::VideoCapture> m_videoCapture;
		std::unique_ptr<cv::VideoWriter> m_videoWriter;
	public:
		ImageGrabberVideo(const ImageGrabberVideo& _other) = delete;
		ImageGrabberVideo(ImageGrabberVideo&& _other) noexcept = delete;
		ImageGrabberVideo& operator=(const ImageGrabberVideo& _other) = delete;
		ImageGrabberVideo& operator=(ImageGrabberVideo&& _other) noexcept = delete;

		DllExport explicit ImageGrabberVideo(const VideoSetting& _videoSetting);
		DllExport ~ImageGrabberVideo() override;

		DllExport cv::Mat GetNewFrame() override;
		DllExport void SaveFrame(const cv::Mat& _saveImage) override;
	};
}

#endif // end of PRIVACYCAM_IMAGE_GRABBER_VIDEO_H
