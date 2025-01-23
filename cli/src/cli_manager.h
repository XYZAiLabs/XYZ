#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <unordered_map>
#include "../../agents/src/agent_manager.h"

namespace xyz {
namespace cli {

class CLIManager {
public:
    static CLIManager& getInstance() {
        static CLIManager instance;
        return instance;
    }

    // Core CLI functionality
    bool initialize();
    void run();
    void shutdown();
    bool processCommand(const std::string& command);

    // CLI customization
    void displayBanner() const;
    void setPrompt(const std::string& newPrompt) { prompt = newPrompt; }
    
private:
    CLIManager();
    ~CLIManager() = default;
    
    // Delete copy constructor and assignment
    CLIManager(const CLIManager&) = delete;
    CLIManager& operator=(const CLIManager&) = delete;

    // Command handlers
    void handleHelp();
    void handleVersion();
    void handleList();
    void handleCreate(const std::vector<std::string>& args);
    void handleStart(const std::vector<std::string>& args);
    void handleStop(const std::vector<std::string>& args);
    void handleStatus();

    // Utility methods
    void displayPrompt() const;
    std::vector<std::string> parseCommand(const std::string& command);
    bool validateArgs(const std::string& cmd, const std::vector<std::string>& args);
    void displayError(const std::string& message) const;

    // Internal state
    bool isRunning;
    std::string prompt;
    std::unordered_map<std::string, 
        std::function<void(const std::vector<std::string>&)>> commandHandlers;
};

} // namespace cli
} // namespace xyz