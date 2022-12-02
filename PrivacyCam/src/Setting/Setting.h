#ifndef PRIVACYCAM_SETTING_H
#define PRIVACYCAM_SETTING_H

#include <PreProcessors.h>
#include <string>

namespace pricam
{
	struct VideoSetting
	{
		std::string InputVideoLocation;
		std::string OutputVideoLocation;
	};

	struct BlurSetting
	{
		bool BlurFace;
		bool BlurPlate;
	};

	enum class StreamType
	{
		VIDEO,
		NONE
	};

	struct Setting
	{
		VideoSetting Video;
		BlurSetting Blur;
		StreamType Stream;
		int ThreadPoolSize;

		DllExport Setting();
		DllExport explicit Setting(const std::string& _settingFilePath);
	};
}

#endif // end of PRIVACYCAM_SETTING_H
