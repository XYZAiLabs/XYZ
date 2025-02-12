#pragma once

#include <string>
#include <vector>
#include <functional>
#include "../cli/src/cli_manager.h"

namespace xyz {
namespace cli {

// Command interface
struct Command {
    std::string name;
    std::string description;
    std::vector<std::string> arguments;
    std::function<bool(const std::vector<std::string>&)> handler;
};

// Public CLI interface
class CLI {
public:
    static CLI& getInstance();

    // Core functionality
    virtual bool initialize() = 0;
    virtual void run() = 0;
    virtual void shutdown() = 0;

    // Command management
    virtual bool registerCommand(const Command& command) = 0;
    virtual bool unregisterCommand(const std::string& name) = 0;
    virtual bool executeCommand(const std::string& command, 
                              const std::vector<std::string>& args) = 0;

    // Customization
    virtual void setPrompt(const std::string& prompt) = 0;
    virtual void enableColors(bool enable) = 0;
    virtual void displayBanner() const = 0;

protected:
    CLI() = default;
    virtual ~CLI() = default;
};

// Result types
enum class CommandResult {
    SUCCESS,
    FAILURE,
    INVALID_ARGS,
    UNKNOWN_COMMAND,
    SYSTEM_ERROR
};

} // namespace cli
} // namespace xyz