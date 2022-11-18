#include "ImageGrabber.h"

#include <opencv2/opencv.hpp>

using namespace pricam;

ImageGrabberVideo::ImageGrabberVideo(const std::string& _videoPath)
{
	m_videoFilePath = _videoPath;
}

cv::Mat ImageGrabberVideo::GetNewFrame()
{
	return cv::Mat();
}