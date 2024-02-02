#ifndef PRIVACYCAM_SETTING_H
#define PRIVACYCAM_SETTING_H

#include <string>

#include "PreProcessors.h"

namespace pricam
{
	struct VideoSetting
	{
		std::string InputVideoPath;
		std::string OutputVideoPath;
	};

	enum class StreamType
	{
		VIDEO,
		NONE
	};

	struct Setting
	{
		VideoSetting Video;
		StreamType Stream;

		DllExport Setting();
	};
}

#endif // end of PRIVACYCAM_SETTING_H
