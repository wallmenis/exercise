#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>

class Logger {
private:
    std::string logFilePath;
public:
    Logger();
    ~Logger();
    void log(const std::string& message);
    void setLogFilePath(const std::string& path);
};

#endif