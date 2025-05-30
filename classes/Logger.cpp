#include "Logger.h"
#include <iostream>
#include <chrono>
#include <format>
std::vector<LogEntry> Logger::messages;

std::string TimeInfo() {
    std::string timeinfo{};
    auto now = std::chrono::system_clock::now();  // tiempo actual del sistema
    auto flooredNow = std::chrono::floor<std::chrono::seconds>(now); // redondeo nano a seg
    auto local_time = std::chrono::zoned_time{ std::chrono::current_zone(), flooredNow };  // zona horaria local

    timeinfo= std::format("[{:%Y-%m-%d %H:%M:%S}] ", local_time);
    if (timeinfo.empty()) {
        return "<time error> ";
    }
    return timeinfo;
}
void Logger::Log(const std::string message) {
    std::string text = TimeInfo() + "\033[1;32m" + message + "\033[0m\n";
    std::cout << text<<"\n";

    LogEntry entry{ LogType{LOG_INFO},text };
    messages.push_back(entry);
}

void Logger::Err(const std::string message) {
    std::string text = "\033[31m" + TimeInfo() + "Error: " + message + "\033[0m\n";
    std::cout << text << "\n";

    LogEntry entry{ LogType{LOG_ERROR},text };
    messages.push_back(entry);
}

