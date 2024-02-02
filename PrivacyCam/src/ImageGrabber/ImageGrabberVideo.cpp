#include "ImageGrabberVideo.h"

#include <filesystem>

#include <opencv2/opencv.hpp>

#include "Setting/Setting.h"

using namespace pricam;
namespace fs = std::filesystem;

ImageGrabberVideo::ImageGrabberVideo(const VideoSetting& _videoSetting)
	: m_frameSize()
	, m_grabbedFrameCount(0)
{
	if (!fs::exists(_videoSetting.InputVideoPath))
		throw std::runtime_error("could not find video file: " + _videoSetting.InputVideoPath);

	m_videoCapture = std::make_unique<cv::VideoCapture>(_videoSetting.InputVideoPath);
	if (!m_videoCapture->isOpened())
		throw std::runtime_error("could not open video capture with video address: " + _videoSetting.InputVideoPath);
	
	m_frameRate = m_videoCapture->get(cv::CAP_PROP_FPS);
	m_frameSize.Width = static_cast<int>(m_videoCapture->get(cv::CAP_PROP_FRAME_WIDTH));
	m_frameSize.Height = static_cast<int>(m_videoCapture->get(cv::CAP_PROP_FRAME_HEIGHT));
	m_videoFrameCount = static_cast<int>(m_videoCapture->get(cv::CAP_PROP_FRAME_COUNT));
	m_videoWriter = std::make_unique<cv::VideoWriter>(_videoSetting.OutputVideoPath, cv::VideoWriter::fourcc('M', 'P', '4', '2'), m_frameRate, cv::Size(m_frameSize.Width, m_frameSize.Height));
	m_grabState = GrabState::ONGOING;
}

ImageGrabberVideo::~ImageGrabberVideo() = default;

cv::Mat ImageGrabberVideo::GetNewFrame()
{
	if (!m_videoCapture->isOpened())
		throw std::runtime_error("couldn't read frame from video");

	cv::Mat newFrame;
	if (!m_videoCapture->read(newFrame) || m_grabbedFrameCount >= m_videoFrameCount)
	{
		m_grabState = GrabState::ENDED;
	}
	++m_grabbedFrameCount;
	return newFrame;
}

void ImageGrabberVideo::SaveFrame(const cv::Mat& _saveImage)
{
	m_videoWriter->write(_saveImage);
}
