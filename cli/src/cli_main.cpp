#include <iostream>
#include <signal.h>
#include "cli_manager.h"
#include "../../utils/logging.h"

using namespace xyz::cli;

// Global pointer for signal handling
static CLIManager* g_cliManager = nullptr;

// Signal handler
void signalHandler(int signum) {
    if (g_cliManager) {
        std::cout << "\nReceived signal " << signum << ", shutting down...\n";
        g_cliManager->shutdown();
    }
}

int main(int argc, char* argv[]) {
    try {
        // Setup signal handling
        g_cliManager = &CLIManager::getInstance();
        signal(SIGINT, signalHandler);
        signal(SIGTERM, signalHandler);

        // Initialize the CLI
        if (!g_cliManager->initialize()) {
            LOG_ERROR("Failed to initialize CLI");
            return 1;
        }

        // Run the CLI
        g_cliManager->run();

        return 0;
    }
    catch (const std::exception& e) {
        LOG_ERROR("Fatal error: " + std::string(e.what()));
        return 1;
    }
}