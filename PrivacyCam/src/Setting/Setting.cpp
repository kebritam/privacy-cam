#include "Setting.h"

#include <fstream>
#include <filesystem>

#include <nlohmann/json.hpp>

using namespace pricam;
using json = nlohmann::json;
namespace fs = std::filesystem;

Setting::Setting()
{
	const fs::path currentPath = fs::current_path().append("config.json");

	std::ifstream configFile(currentPath);
	if (configFile.fail())
		throw std::runtime_error("error in opening config file: " + currentPath.generic_string());

	json jsonSetting = json::parse(configFile);

	Video.InputVideoPath = jsonSetting["VideoSetting"].value("InputVideoPath", "");
	Video.OutputVideoPath = jsonSetting["VideoSetting"].value("OutputVideoPath", "");

	if ("Video" == jsonSetting.value("StreamType", ""))
		Stream = StreamType::VIDEO;
	else
		Stream = StreamType::NONE;
}
