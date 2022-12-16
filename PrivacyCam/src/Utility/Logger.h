#ifndef PRICAM_LOGGING_BASE_H
#define PRICAM_LOGGING_BASE_H

#include <string>
#include <PreProcessors.h>
#include <memory>
#include <spdlog/logger.h>

namespace behkhan
{
	enum class LogType
	{
		Debug,
		Info,
		Warn,
		Error,
		Fatal
	};

#define FILENAME (strrchr(__FILE__, PathSeparator) ? strrchr(__FILE__, PathSeparator) + 1 : __FILE__)

#define																											\
	LOG_DEBUG(x, ...) do{																						\
		Logger::GetInstance().Log(FILENAME, __FUNCTION__, __LINE__, x, LogType::Debug, ##__VA_ARGS__);			\
	} while(0)

#define																											\
	LOG_INFO(x, ...) do{																						\
		Logger::GetInstance().Log(FILENAME, __FUNCTION__, __LINE__, x, LogType::Info,  ##__VA_ARGS__);			\
	} while(0)

#define																											\
	LOG_WARN(x, ...) do{																						\
		Logger::GetInstance().Log(FILENAME, __FUNCTION__, __LINE__, x, LogType::Warn,  ##__VA_ARGS__);			\
	} while(0)

#define																											\
	LOG_ERROR(x, ...) do{																						\
		Logger::GetInstance().Log(FILENAME, __FUNCTION__, __LINE__, x, LogType::Error, ##__VA_ARGS__);			\
	} while(0)

#define																											\
	LOG_FATAL(x, ...) do{																						\
		Logger::GetInstance().Log(FILENAME, __FUNCTION__, __LINE__, x, LogType::Fatal, ##__VA_ARGS__);			\
	} while(0)

	class Logger
	{
		std::shared_ptr<spdlog::logger> m_logger;
	public:
		Logger(const Logger& _other) = delete;
		Logger(Logger&& _other) noexcept = delete;
		Logger& operator=(const Logger& _other) = delete;
		Logger& operator=(Logger&& _other) noexcept = delete;

		DllExport Logger();
		DllExport ~Logger();

		DllExport static Logger& GetInstance();

		DllExport void InitLogging();

		template<typename... Args>
		DllExport void Log(const char* _fileName, const char* _functionName, const int _line, const std::string& _msg, const LogType _logType, const Args &... _args)
		{
			std::string ss = std::string(_fileName) + "|" + std::string(_functionName) + "|" + std::to_string(_line) + "|" + _msg;
			switch (_logType)
			{
			case LogType::Debug:
				m_logger->debug(ss, _args...);
				break;

			case LogType::Info:
				m_logger->info(ss, _args...);
				break;

			case LogType::Warn:
				m_logger->warn(ss, _args...);
				break;

			case LogType::Error:
				m_logger->error(ss, _args...);
				m_logger->flush();
				break;

			case LogType::Fatal:
				m_logger->critical(ss, _args...);
				m_logger->flush();
				break;
			}
		}
	};
}

#endif
