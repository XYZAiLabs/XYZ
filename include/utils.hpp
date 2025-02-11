#pragma once

#include <string>
#include <memory>
#include <variant>
#include "../utils/logging.h"
#include "../utils/config_loader.h"
#include "../utils/constants.h"

namespace xyz {
namespace utils {

// Public logging interface
class Logger {
public:
    enum class Level {
        TRACE,
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        FATAL
    };

    static Logger& getInstance();

    virtual void log(Level level, const std::string& message,
                    const std::string& file = "", int line = 0,
                    const std::string& function = "") = 0;
    
    virtual void setLogFile(const std::string& path) = 0;
    virtual void setLogLevel(Level level) = 0;
    virtual void enableConsoleOutput(bool enable) = 0;
    virtual void enableFileOutput(bool enable) = 0;

protected:
    Logger() = default;
    virtual ~Logger() = default;
};

// Public configuration interface
class Config {
public:
    using Value = std::variant<std::string, int, double, bool>;
    using ConfigMap = std::unordered_map<std::string, Value>;

    static Config& getInstance();

    virtual bool load(const std::string& path) = 0;
    virtual bool save(const std::string& path) const = 0;
    
    template<typename T>
    T getValue(const std::string& key, const T& defaultValue = T()) const;
    
    virtual bool setValue(const std::string& key, const Value& value) = 0;
    virtual bool hasKey(const std::string& key) const = 0;
    virtual ConfigMap getAll() const = 0;

protected:
    Config() = default;
    virtual ~Config() = default;
};

// Utility functions
namespace system {
    std::string getVersion();
    std::string getPlatform();
    size_t getMemoryUsage();
    double getCPUUsage();
    std::string getTimestamp();
}

// Error handling
class Error : public std::exception {
public:
    explicit Error(const std::string& message) : msg(message) {}
    const char* what() const noexcept override { return msg.c_str(); }

private:
    std::string msg;
};

} // namespace utils
} // namespace xyz

// Convenience macros
#define XYZ_LOG_INFO(msg) xyz::utils::Logger::getInstance().log( \
    xyz::utils::Logger::Level::INFO, msg, __FILE__, __LINE__, __FUNCTION__)
#define XYZ_LOG_ERROR(msg) xyz::utils::Logger::getInstance().log( \
    xyz::utils::Logger::Level::ERROR, msg, __FILE__, __LINE__, __FUNCTION__)