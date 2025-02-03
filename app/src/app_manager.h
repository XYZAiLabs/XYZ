#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "../../agents/src/agent_manager.h"
#include "../../models/src/model.h"

namespace xyz {
namespace app {

class AppManager {
public:
    static AppManager& getInstance() {
        static AppManager instance;
        return instance;
    }

    // Core application management
    bool initialize(const std::string& configPath = "config/app.json");
    bool run();
    void shutdown();
    bool isRunning() const { return running; }

    // Application configuration
    bool loadConfig(const std::string& configPath);
    bool saveConfig(const std::string& configPath);

    // System management
    bool startSystem();
    bool stopSystem();
    bool restartSystem();
    
    // Resource management
    bool allocateResources();
    void releaseResources();
    
    // Status and monitoring
    struct SystemStatus {
        size_t activeAgents;
        size_t pendingTasks;
        double cpuUsage;
        size_t memoryUsage;
        std::string state;
    };
    
    SystemStatus getSystemStatus() const;
    std::string getVersion() const { return "1.0.0"; }

private:
    AppManager();
    ~AppManager();
    
    // Delete copy constructor and assignment operator
    AppManager(const AppManager&) = delete;
    AppManager& operator=(const AppManager&) = delete;

    // Internal methods
    bool initializeSubsystems();
    bool validateConfiguration();
    void monitorSystem();
    
    // Internal state
    bool running;
    bool initialized;
    std::unordered_map<std::string, std::string> config;
    std::unique_ptr<xyz::AgentManager> agentManager;
    SystemStatus currentStatus;
};

} // namespace app
} // namespace xyz