#include <iostream>
#include <csignal>
#include "app_manager.h"
#include "../../utils/logging.h"

using namespace xyz::app;

// Global pointer for signal handling
static AppManager* g_appManager = nullptr;

// Signal handler
void signalHandler(int signum) {
    if (g_appManager) {
        LOG_INFO("Received signal " + std::to_string(signum) + ", initiating shutdown");
        g_appManager->shutdown();
    }
}

int main(int argc, char* argv[]) {
    try {
        // Setup signal handling
        g_appManager = &AppManager::getInstance();
        signal(SIGINT, signalHandler);
        signal(SIGTERM, signalHandler);

        LOG_INFO("Starting XYZ Framework Application");
        
        // Initialize the application
        if (!g_appManager->initialize()) {
            LOG_ERROR("Failed to initialize application");
            return 1;
        }

        // Display startup information
        std::cout << "XYZ Framework v" << g_appManager->getVersion() << "\n";
        std::cout << "Initialization complete. Starting main loop...\n";

        // Run the application
        if (!g_appManager->run()) {
            LOG_ERROR("Application runtime error");
            return 1;
        }

        LOG_INFO("Application shutting down normally");
        return 0;
    }
    catch (const std::exception& e) {
        LOG_ERROR("Fatal error: " + std::string(e.what()));
        return 1;
    }
}