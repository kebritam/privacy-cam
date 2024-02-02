#ifndef PRIVACYCAM_PIPELINE_H
#define PRIVACYCAM_PIPELINE_H

#include <memory>

#include "PreProcessors.h"

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

		double m_pipeDuration = 0.;
		double m_grabFrameDuration = 0.;
		double m_detectFacesDuration = 0.;
		double m_detectPlatesDuration = 0.;
		double m_blurDuration = 0.;
		double m_saveFrameDuration = 0.;

		[[nodiscard]] std::unique_ptr<PipelineElement> grabFrame(std::unique_ptr<PipelineElement> _pipelineElement);
		[[nodiscard]] std::unique_ptr<PipelineElement> detectFaces(std::unique_ptr<PipelineElement> _pipelineElement);
		[[nodiscard]] std::unique_ptr<PipelineElement> blur(std::unique_ptr<PipelineElement> _pipelineElement);
		[[nodiscard]] std::unique_ptr<PipelineElement> saveFrame(std::unique_ptr<PipelineElement> _pipelineElement);

		void optForFinishing();
		void processPipes() const;

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
