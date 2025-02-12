#pragma once

#include <string>
#include <memory>
#include "../app/src/app_manager.h"

namespace xyz {
namespace app {

// Public application interface
class Application {
public:
    static Application& getInstance();

    // Core functionality
    virtual bool initialize(const std::string& configPath = "") = 0;
    virtual bool run() = 0;
    virtual void shutdown() = 0;

    // Status and monitoring
    struct SystemStatus {
        size_t activeAgents;
        size_t pendingTasks;
        double cpuUsage;
        size_t memoryUsage;
        std::string state;
    };

    virtual SystemStatus getStatus() const = 0;
    virtual std::string getVersion() const = 0;
    virtual bool isRunning() const = 0;

protected:
    Application() = default;
    virtual ~Application() = default;
};

// Configuration interface
struct AppConfig {
    std::string appName;
    std::string version;
    std::string logLevel;
    size_t maxAgents;
    bool debugMode;
};

} // namespace app
} // namespace xyz