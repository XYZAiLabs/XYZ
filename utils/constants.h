#pragma once

#include <string>
#include <array>

namespace xyz {
namespace constants {

// Version information
constexpr auto VERSION_MAJOR = 1;
constexpr auto VERSION_MINOR = 0;
constexpr auto VERSION_PATCH = 0;
constexpr auto VERSION_STRING = "1.0.0";

// System limits
constexpr auto MAX_AGENTS = 1000;
constexpr auto MAX_MODELS = 100;
constexpr auto MAX_CONNECTIONS = 500;
constexpr auto MAX_BATCH_SIZE = 256;
constexpr auto MAX_QUEUE_SIZE = 1000;

// Timeouts and intervals (in milliseconds)
constexpr auto DEFAULT_TIMEOUT = 5000;
constexpr auto MIN_UPDATE_INTERVAL = 10;
constexpr auto MAX_UPDATE_INTERVAL = 1000;
constexpr auto HEARTBEAT_INTERVAL = 1000;

// Memory limits (in bytes)
constexpr auto MAX_MEMORY_PER_AGENT = 1024 * 1024 * 100;  // 100 MB
constexpr auto MAX_TOTAL_MEMORY = 1024 * 1024 * 1024 * 2; // 2 GB

// File paths and extensions
struct Paths {
    static const std::string CONFIG_DIR;
    static const std::string LOG_DIR;
    static const std::string MODEL_DIR;
    static const std::string CACHE_DIR;
    static const std::string DEFAULT_CONFIG;
};

// Error codes
enum class ErrorCode {
    SUCCESS = 0,
    INITIALIZATION_ERROR = 1,
    CONFIGURATION_ERROR = 2,
    RESOURCE_ERROR = 3,
    NETWORK_ERROR = 4,
    MODEL_ERROR = 5,
    AGENT_ERROR = 6,
    TIMEOUT_ERROR = 7,
    UNKNOWN_ERROR = 999
};

// Status codes
enum class StatusCode {
    OK = 0,
    WARNING = 1,
    ERROR = 2,
    CRITICAL = 3
};

// Configuration keys
struct ConfigKeys {
    static const std::string LOG_LEVEL;
    static const std::string MAX_THREADS;
    static const std::string ENABLE_DEBUG;
    static const std::string MODEL_TYPE;
    static const std::string AGENT_CONFIG;
};

// Default configuration values
struct Defaults {
    static const std::string LOG_LEVEL;
    static constexpr int MAX_THREADS = 4;
    static constexpr bool ENABLE_DEBUG = false;
    static const std::string MODEL_TYPE;
};

// Supported model types
const std::array<std::string, 5> SUPPORTED_MODELS = {
    "neural_network",
    "decision_tree",
    "random_forest",
    "svm",
    "custom"
};

// Error messages
struct ErrorMessages {
    static const std::string INIT_FAILED;
    static const std::string CONFIG_NOT_FOUND;
    static const std::string INVALID_MODEL;
    static const std::string AGENT_CREATION_FAILED;
    static const std::string RESOURCE_EXHAUSTED;
};

} // namespace constants
} // namespace xyz