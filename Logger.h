#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <vector>
enum LogType {
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR
};

struct LogEntry {
	LogType type{};
	std::string message{};
};

class Logger
{
public:
	//static es para que se pueda usar Logger::Log("sus"), estructura (singleton-like);
	static std::vector<LogEntry> messages;
	static void Log(const std::string message);
	static void Err(const std::string message);
};

#endif

