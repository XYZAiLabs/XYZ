#pragma once

#include <string>
#include <sstream>
#include <memory>
#include <mutex>
#include <fstream>
#include "constants.h"

namespace xyz {
namespace utils {

enum class LogLevel {
    TRACE,
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL
};

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    // Core logging functions
    void log(LogLevel level, const std::string& message, 
             const std::string& file, int line, const std::string& function);
    
    // Configuration
    void setLogFile(const std::string& path);
    void setLogLevel(LogLevel level) { minimumLevel = level; }
    void enableConsoleOutput(bool enable) { consoleOutput = enable; }
    void enableFileOutput(bool enable) { fileOutput = enable; }
    void enableColors(bool enable) { useColors = enable; }

    // Utility functions
    std::string getLevelString(LogLevel level) const;
    std::string getTimestamp() const;

private:
    Logger();
    ~Logger();
    
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // Internal methods
    void openLogFile();
    void writeToFile(const std::string& message);
    void writeToConsole(const std::string& message, LogLevel level);
    std::string formatMessage(LogLevel level, const std::string& message,
                            const std::string& file, int line, 
                            const std::string& function) const;

    // State
    LogLevel minimumLevel;
    bool consoleOutput;
    bool fileOutput;
    bool useColors;
    std::string logFilePath;
    std::unique_ptr<std::ofstream> logFile;
    std::mutex mutex;
};

} // namespace utils
} // namespace xyz

// Convenience macros
#define LOG_TRACE(message) xyz::utils::Logger::getInstance().log( \
    xyz::utils::LogLevel::TRACE, message, __FILE__, __LINE__, __FUNCTION__)
#define LOG_DEBUG(message) xyz::utils::Logger::getInstance().log( \
    xyz::utils::LogLevel::DEBUG, message, __FILE__, __LINE__, __FUNCTION__)
#define LOG_INFO(message) xyz::utils::Logger::getInstance().log( \
    xyz::utils::LogLevel::INFO, message, __FILE__, __LINE__, __FUNCTION__)
#define LOG_WARNING(message) xyz::utils::Logger::getInstance().log( \
    xyz::utils::LogLevel::WARNING, message, __FILE__, __LINE__, __FUNCTION__)
#define LOG_ERROR(message) xyz::utils::Logger::getInstance().log( \
    xyz::utils::LogLevel::ERROR, message, __FILE__, __LINE__, __FUNCTION__)
#define LOG_FATAL(message) xyz::utils::Logger::getInstance().log( \
    xyz::utils::LogLevel::FATAL, message, __FILE__, __LINE__, __FUNCTION__)