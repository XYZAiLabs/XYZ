#include <iostream>
#include "agent_manager.h"
#include "ai_processor.h"
#include "../../utils/logging.h"

int main(int argc, char* argv[]) {
    try {
        LOG_INFO("Initializing XYZ Agents Module...");

        // Initialize AI Processor
        auto& processor = xyz::AIProcessor::getInstance();
        if (!processor.initialize()) {
            LOG_ERROR("Failed to initialize AI Processor");
            return 1;
        }

        // Initialize Agent Manager
        auto& manager = xyz::AgentManager::getInstance();
        if (!manager.configure("config/agents.json")) {
            LOG_ERROR("Failed to configure Agent Manager");
            return 1;
        }

        // Create a test agent
        auto agent = manager.createAgent("test_agent");
        if (!agent) {
            LOG_ERROR("Failed to create test agent");
            return 1;
        }

        // Start the agent
        if (!agent->start()) {
            LOG_ERROR("Failed to start test agent");
            return 1;
        }

        LOG_INFO("XYZ Agents Module initialized successfully");
        
        // Wait for shutdown signal
        std::string input;
        std::cout << "Press Enter to shutdown..." << std::endl;
        std::getline(std::cin, input);

        // Cleanup
        manager.destroyAllAgents();
        processor.shutdown();

        LOG_INFO("XYZ Agents Module shutdown complete");
        return 0;
    }
    catch (const std::exception& e) {
        LOG_ERROR("Fatal error: " + std::string(e.what()));
        return 1;
    }
}