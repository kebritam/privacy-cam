#include "ImageGrabberVideo.h"

#include <filesystem>

#include "opencv2/opencv.hpp"
#include "Setting/Setting.h"

using namespace pricam;
namespace fs = std::filesystem;

ImageGrabberVideo::ImageGrabberVideo(const VideoSetting& _videoSetting) :
	m_frameSize()
{
	if (!fs::exists(_videoSetting.InputVideoLocation))
		throw std::runtime_error("could not find video file: " + _videoSetting.InputVideoLocation);

	if (!fs::is_directory(_videoSetting.OutputVideoLocation) || !fs::exists(_videoSetting.OutputVideoLocation))
		throw std::runtime_error("could not find output directory: " + _videoSetting.OutputVideoLocation);

	m_videoCapture = std::make_unique<cv::VideoCapture>(_videoSetting.InputVideoLocation);
	if (!m_videoCapture->isOpened())
		throw std::runtime_error("could not open video capture with video address: " + _videoSetting.InputVideoLocation);
	
	m_frameRate = m_videoCapture->get(cv::CAP_PROP_FPS);
	m_frameSize.Width = static_cast<int>(m_videoCapture->get(cv::CAP_PROP_FRAME_WIDTH));
	m_frameSize.Height = static_cast<int>(m_videoCapture->get(cv::CAP_PROP_FRAME_HEIGHT));
	m_videoWriter = std::make_unique<cv::VideoWriter>(_videoSetting.OutputVideoLocation + PathSeparator + "video.avi", cv::VideoWriter::fourcc('M', 'P', '4', '2'), m_frameRate, cv::Size(m_frameSize.Width, m_frameSize.Height));
	m_grabState = GrabState::ONGOING;
}

ImageGrabberVideo::~ImageGrabberVideo() = default;

cv::Mat ImageGrabberVideo::GetNewFrame()
{
	cv::Mat newFrame;
	if (m_videoCapture->isOpened())
	{
		const bool readRes = m_videoCapture->read(newFrame);
		if (!readRes)
		{
			m_grabState = GrabState::ENDED;
		}
	}
	else
	{
		throw std::runtime_error("could not open cv::VideoCapture");
	}
	return newFrame;
}

void ImageGrabberVideo::SaveFrame(const cv::Mat& _saveImage)
{
	m_videoWriter->write(_saveImage);
}
