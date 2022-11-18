#ifndef PRIVACYCAM_IMAGE_GRABBER_H
#define PRIVACYCAM_IMAGE_GRABBER_H

#include <PreProcessors.h>
#include <string>

namespace cv
{
	class Mat;
}

namespace pricam
{
	class ImageGrabber
	{
	public:
		DllExport virtual cv::Mat GetNewFrame() = 0;
	};

	class ImageGrabberVideo : public ImageGrabber
	{
		std::string m_videoFilePath;
	public:
		DllExport ImageGrabberVideo(const std::string& _videoPath);
		DllExport cv::Mat GetNewFrame() override;
	};
}

#endif // end of PRIVACYCAM_IMAGE_GRABBER_H
