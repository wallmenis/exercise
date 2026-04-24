#include "logger.h"

#include <iostream>
#include <ctime>

Logger::Logger() : logFilePath("") {}
Logger::~Logger() {}

void Logger::log(const std::string& message) {
    if (logFilePath.empty()) {
        std::cerr << "ERROR: Log file path not set. Please set it using Logger::setLogFilePath().\n";
        return;
    }
    std::ofstream logFile(logFilePath, std::ios_base::app);
    if (logFile.is_open()) {
        logFile << time(nullptr) << ": " << message << std::endl;
        logFile.close();
    } else {
        std::cerr << "ERROR: Could not open log file at " << logFilePath << std::endl;
    }
}

void Logger::setLogFilePath(const std::string& path) {
    logFilePath = path;
}