#include "Setting.h"

#include <fstream>
#include <filesystem>

#include "nlohmann/json.hpp"

using namespace pricam;
using json = nlohmann::json;
namespace fs = std::filesystem;

Setting::Setting() :
	Setting("config.json")
{
}

Setting::Setting(const std::string& _settingFileName)
{
	fs::path currentPath = fs::current_path();
	currentPath.append(_settingFileName);

	std::ifstream configFile(currentPath);
	if (configFile.fail())
		throw std::runtime_error("error in opening config file: " + currentPath.generic_string());

	json jsonSetting = json::parse(configFile);

	Video.InputVideoLocation = jsonSetting["VideoSetting"].value("InputVideoLocation", "");
	Video.OutputVideoLocation = jsonSetting["VideoSetting"].value("OutputVideoLocation", "");
	Blur.BlurFace = jsonSetting["BlurSetting"].value("BlurFace", false);
	Blur.BlurPlate = jsonSetting["BlurSetting"].value("BlurPlate", false);

	if ("Video" == jsonSetting.value("StreamType", "Video"))
		Stream = StreamType::VIDEO;
	else
		Stream = StreamType::NONE;

	ThreadPoolSize = jsonSetting.value("ThreadPoolSize", 4);
}
