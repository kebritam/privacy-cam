#include "ImageGrabberVideo.h"

#include <filesystem>

#include "opencv2/opencv.hpp"

using namespace pricam;
namespace fs = std::filesystem;

ImageGrabberVideo::ImageGrabberVideo(const std::string& _videoPath)
{
	if (!fs::exists(_videoPath))
		throw std::runtime_error("could not find video file: " + _videoPath);

	m_videoCapture = std::make_unique<cv::VideoCapture>(_videoPath);
}

ImageGrabberVideo::~ImageGrabberVideo() = default;

cv::Mat ImageGrabberVideo::GetNewFrame()
{
	cv::Mat newFrame;
	if (m_videoCapture->isOpened())
		m_videoCapture->read(newFrame);
	else
		throw std::runtime_error("could not open cv::VideoCapture");
	return newFrame;
}