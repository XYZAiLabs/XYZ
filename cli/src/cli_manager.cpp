#include "cli_manager.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "../../utils/logging.h"

namespace xyz {
namespace cli {

CLIManager::CLIManager() : isRunning(false), prompt("xyz> ") {
    // Initialize command handlers
    commandHandlers["help"] = [this](const auto&) { this->handleHelp(); };
    commandHandlers["version"] = [this](const auto&) { this->handleVersion(); };
    commandHandlers["list"] = [this](const auto&) { this->handleList(); };
    commandHandlers["create"] = [this](const auto& args) { this->handleCreate(args); };
    commandHandlers["start"] = [this](const auto& args) { this->handleStart(args); };
    commandHandlers["stop"] = [this](const auto& args) { this->handleStop(args); };
    commandHandlers["status"] = [this](const auto&) { this->handleStatus(); };
}

void CLIManager::displayBanner() const {
    // ANSI color codes
    const std::string BLUE = "\033[34m";
    const std::string GREEN = "\033[32m";
    const std::string RESET = "\033[0m";
    const std::string BOLD = "\033[1m";

    std::cout << BLUE << BOLD << R"(

$$\   $$\ $$\     $$\ $$$$$$$$\ 
$$ |  $$ |\$$\   $$  |\____$$  |
\$$\ $$  | \$$\ $$  /     $$  / 
 \$$$$  /   \$$$$  /     $$  /  
 $$  $$<     \$$  /     $$  /   
$$  /\$$\     $$ |     $$  /    
$$ /  $$ |    $$ |    $$$$$$$$\ 
\__|  \__|    \__|    \________|
                                
)" << RESET << "\n";

    std::cout << GREEN << "XYZ AI Agent Framework CLI v1.0.0" << RESET << "\n";
    std::cout << "Type 'help' for available commands\n\n";
}

bool CLIManager::initialize() {
    LOG_INFO("Initializing XYZ CLI Manager");
    isRunning = true;
    displayBanner();
    return true;
}

void CLIManager::run() {
    std::string input;
    
    while (isRunning) {
        displayPrompt();
        std::getline(std::cin, input);
        
        if (input == "exit" || input == "quit") {
            break;
        }
        
        processCommand(input);
    }
}

bool CLIManager::processCommand(const std::string& command) {
    auto tokens = parseCommand(command);
    if (tokens.empty()) return false;

    std::string cmd = tokens[0];
    std::vector<std::string> args(tokens.begin() + 1, tokens.end());

    auto it = commandHandlers.find(cmd);
    if (it != commandHandlers.end()) {
        try {
            it->second(args);
            return true;
        }
        catch (const std::exception& e) {
            displayError(e.what());
            return false;
        }
    }

    displayError("Unknown command: " + cmd);
    return false;
}

void CLIManager::handleHelp() {
    std::cout << "\nAvailable Commands:\n";
    std::cout << std::setw(20) << std::left << "  help" << "Display this help message\n";
    std::cout << std::setw(20) << std::left << "  version" << "Display version information\n";
    std::cout << std::setw(20) << std::left << "  list" << "List all active agents\n";
    std::cout << std::setw(20) << std::left << "  create <type>" << "Create a new agent\n";
    std::cout << std::setw(20) << std::left << "  start <id>" << "Start an agent\n";
    std::cout << std::setw(20) << std::left << "  stop <id>" << "Stop an agent\n";
    std::cout << std::setw(20) << std::left << "  status" << "Display system status\n";
    std::cout << std::setw(20) << std::left << "  exit" << "Exit the CLI\n\n";
}

// ... Other handler implementations ...

void CLIManager::displayPrompt() const {
    std::cout << prompt;
}

std::vector<std::string> CLIManager::parseCommand(const std::string& command) {
    std::vector<std::string> tokens;
    std::stringstream ss(command);
    std::string token;
    
    while (ss >> token) {
        tokens.push_back(token);
    }
    
    return tokens;
}

void CLIManager::displayError(const std::string& message) const {
    std::cout << "\033[31mError: " << message << "\033[0m\n";
}

void CLIManager::shutdown() {
    isRunning = false;
    LOG_INFO("CLI Manager shutdown complete");
}

} // namespace cli
} // namespace xyz