#include "Logger.h"

#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

using namespace pricam;

Logger::Logger()
{
	initLogging();
}

Logger::~Logger() = default;

Logger& Logger::GetInstance()
{
	static Logger logger;
	return logger;
}

void Logger::initLogging()
{
	//default values
	const std::string logFilesDirectory = "./Logs";
	const std::string level = "INFO";
	const std::string display = "false";

	auto maxSize = 1048576 * 100;
	auto maxFiles = 10;
	std::vector<spdlog::sink_ptr> sinks;

	spdlog::init_thread_pool(8192, 1);
	if (display == "true")
	{
		const auto stdoutSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		sinks.push_back(stdoutSink);
	}

	const auto rotatingSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(logFilesDirectory + PathSeparator + "PricamLog.txt", maxSize, maxFiles);
	sinks.push_back(rotatingSink);
	m_logger = std::make_shared<spdlog::async_logger>("pricam", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);

	if (level == "Debug")
	{
		m_logger->set_level(spdlog::level::debug);
	}
	if (level == "INFO")
	{
		m_logger->set_level(spdlog::level::info);
	}
	else if (level == "WARNING")
	{
		m_logger->set_level(spdlog::level::warn);
	}
	else
	{
		m_logger->set_level(spdlog::level::err);
	}

	m_logger->flush_on(spdlog::level::err);
	register_logger(m_logger);

	std::cout << "Logger started..." << std::endl;
	m_logger->info("Logger started...");
}
