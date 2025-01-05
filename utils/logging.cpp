#include "logging.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>

namespace xyz {
namespace utils {

Logger::Logger()
    : minimumLevel(LogLevel::INFO)
    , consoleOutput(true)
    , fileOutput(false)
    , useColors(true)
{
    logFilePath = "xyz_framework.log";
}

Logger::~Logger() {
    if (logFile && logFile->is_open()) {
        logFile->close();
    }
}

void Logger::log(LogLevel level, const std::string& message,
                const std::string& file, int line, const std::string& function) {
    if (level < minimumLevel) {
        return;
    }

    std::string formattedMessage = formatMessage(level, message, file, line, function);
    
    std::lock_guard<std::mutex> lock(mutex);
    
    if (consoleOutput) {
        writeToConsole(formattedMessage, level);
    }
    
    if (fileOutput) {
        writeToFile(formattedMessage);
    }
}

void Logger::setLogFile(const std::string& path) {
    std::lock_guard<std::mutex> lock(mutex);
    logFilePath = path;
    openLogFile();
}

void Logger::openLogFile() {
    if (logFile && logFile->is_open()) {
        logFile->close();
    }
    
    logFile = std::make_unique<std::ofstream>(logFilePath, std::ios::app);
    if (!logFile->is_open()) {
        std::cerr << "Failed to open log file: " << logFilePath << std::endl;
        fileOutput = false;
    }
}

std::string Logger::getLevelString(LogLevel level) const {
    switch (level) {
        case LogLevel::TRACE:   return "TRACE";
        case LogLevel::DEBUG:   return "DEBUG";
        case LogLevel::INFO:    return "INFO";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::ERROR:   return "ERROR";
        case LogLevel::FATAL:   return "FATAL";
        default:                return "UNKNOWN";
    }
}

std::string Logger::getTimestamp() const {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;

    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S")
       << '.' << std::setfill('0') << std::setw(3) << ms.count();
    
    return ss.str();
}

void Logger::writeToConsole(const std::string& message, LogLevel level) {
    if (!useColors) {
        std::cout << message << std::endl;
        return;
    }

    // ANSI color codes
    const char* colorCode = "\033[0m";
    switch (level) {
        case LogLevel::TRACE:   colorCode = "\033[37m"; break; // White
        case LogLevel::DEBUG:   colorCode = "\033[36m"; break; // Cyan
        case LogLevel::INFO:    colorCode = "\033[32m"; break; // Green
        case LogLevel::WARNING: colorCode = "\033[33m"; break; // Yellow
        case LogLevel::ERROR:   colorCode = "\033[31m"; break; // Red
        case LogLevel::FATAL:   colorCode = "\033[35m"; break; // Magenta
    }

    std::cout << colorCode << message << "\033[0m" << std::endl;
}

void Logger::writeToFile(const std::string& message) {
    if (!logFile || !logFile->is_open()) {
        openLogFile();
    }
    
    if (logFile && logFile->is_open()) {
        *logFile << message << std::endl;
        logFile->flush();
    }
}

std::string Logger::formatMessage(LogLevel level, const std::string& message,
                                const std::string& file, int line,
                                const std::string& function) const {
    std::stringstream ss;
    ss << "[" << getTimestamp() << "] "
       << "[" << getLevelString(level) << "] "
       << "[" << file << ":" << line << "] "
       << "[" << function << "] "
       << message;
    
    return ss.str();
}

} // namespace utils
} // namespace xyz