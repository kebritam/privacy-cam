#ifndef PRIVACYCAM_PIPELINE_H
#define PRIVACYCAM_PIPELINE_H

#include <PreProcessors.h>
#include <memory>
#include <vector>

namespace BS
{
	class thread_pool;
}

namespace pricam
{
	class FaceAnalyzer;
	class PipelineElement;
	class ImageGrabber;
	struct Setting;

	class Pipeline
	{
		std::unique_ptr<BS::thread_pool> m_threadPool;
		std::unique_ptr<ImageGrabber> m_imageGrabber;
		std::unique_ptr<FaceAnalyzer> m_faceAnalyzer;
		bool m_isPipelineStopped;

		std::unique_ptr<PipelineElement> grabFrame(std::unique_ptr<PipelineElement>&& _pipelineElement) const;
		std::unique_ptr<PipelineElement> detectFaces(std::unique_ptr<PipelineElement>&& _pipelineElement) const;
		std::unique_ptr<PipelineElement> detectPlates(std::unique_ptr<PipelineElement>&& _pipelineElement);
		std::unique_ptr<PipelineElement> blur(std::unique_ptr<PipelineElement>&& _pipelineElement) const;
		std::unique_ptr<PipelineElement> saveFrame(std::unique_ptr<PipelineElement>&& _pipelineElement) const;

		void optForFinishing();
		void processPipes(std::vector<std::unique_ptr<PipelineElement>> _elements);
	public:
		Pipeline(const Pipeline& _other) = delete;
		Pipeline(Pipeline&& _other) noexcept = delete;
		Pipeline& operator=(const Pipeline& _other) = delete;
		Pipeline& operator=(Pipeline&& _other) noexcept = delete;

		DllExport explicit Pipeline(const Setting& _setting);
		DllExport ~Pipeline();

		DllExport void Run();
	};
}

#endif // end of PRIVACYCAM_PIPELINE_H
