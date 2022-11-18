#ifndef PRIVACYCAM_PIPELINE_H
#define PRIVACYCAM_PIPELINE_H

#include <PreProcessors.h>
#include <memory>
#include <vector>

#include <opencv2/opencv.hpp>

namespace pricam
{
	class ThreadPool;
	class ImageGrabber;
	struct Setting;

	class PipelineElement
	{
		std::unique_ptr<cv::Mat> m_frame;
		std::vector<cv::Rect> m_rects;

	public:
		PipelineElement(const cv::Mat& _frame);
		PipelineElement(const cv::Mat& _frame, const std::vector<cv::Rect>& _rects);

		cv::Mat GetFrame();
		cv::Rect GetRect(int _idx);
	};

	class Pipeline
	{
		std::unique_ptr<ThreadPool> m_threadPool;
		std::unique_ptr<ImageGrabber> m_imageGrabber;
		bool m_isPipelineStopped;
		
		std::shared_ptr<PipelineElement> grabFrame();
		std::shared_ptr<PipelineElement> detectFaces(const std::shared_ptr<PipelineElement>& _pipelineElement);
		std::shared_ptr<PipelineElement> detectPlates(const std::shared_ptr<PipelineElement>& _pipelineElement);
		std::shared_ptr<PipelineElement> blur(const std::shared_ptr<PipelineElement>& _pipelineElement);
		std::shared_ptr<PipelineElement> saveFrame(const std::shared_ptr<PipelineElement>& _pipelineElement);

		void processPipes();
	public:
		DllExport Pipeline(const Setting& _setting);
		DllExport ~Pipeline();

		DllExport void Run();
	};
}

#endif // end of PRIVACYCAM_PIPELINE_H
