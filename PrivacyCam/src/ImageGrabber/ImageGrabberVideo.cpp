#include "ImageGrabberVideo.h"

#include <filesystem>

#include <opencv2/opencv.hpp>

using namespace pricam;
namespace fs = std::filesystem;

ImageGrabberVideo::ImageGrabberVideo(const std::string& _videoPath)
{
	if(fs::is_regular_file(_videoPath) && !fs::exists(_videoPath))
	{
		throw std::runtime_error("could not find video file: " + _videoPath);
	}
	m_videoCapture = std::make_unique<cv::VideoCapture>(_videoPath);
}

cv::Mat ImageGrabberVideo::GetNewFrame()
{
	return cv::Mat();
}