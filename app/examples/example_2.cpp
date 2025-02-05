#include <iostream>
#include <memory>
#include "../../agents/src/agent_manager.h"
#include "../../models/src/model.h"
#include "../../utils/logging.h"

// Example 2: Multi-Agent Collaboration System
// This example demonstrates how multiple agents can work together
// to solve a complex task through collaboration and message passing.

using namespace xyz;

// Custom collaborative agent class
class CollaborativeAgent : public BaseAgent {
public:
    CollaborativeAgent(const std::string& id, const std::string& type)
        : BaseAgent(id, type) {}

    void sendMessage(const std::string& targetId, const std::string& message) {
        // Simulate message sending
        LOG_INFO("Agent " + getId() + " sending message to " + targetId + ": " + message);
    }

    void receiveMessage(const std::string& fromId, const std::string& message) {
        LOG_INFO("Agent " + getId() + " received message from " + fromId + ": " + message);
        processMessage(fromId, message);
    }

private:
    void processMessage(const std::string& fromId, const std::string& message) {
        // Simulate message processing and state update
        std::cout << "Processing message from " << fromId << "...\n";
        // Update internal state based on message
    }
};

// Simulated task environment
class TaskEnvironment {
public:
    TaskEnvironment() : taskCompleted(false) {}

    void updateState(const std::string& agentId, const std::vector<float>& data) {
        std::cout << "Agent " << agentId << " updated environment state\n";
        // Simulate environment state update
        if (checkTaskCompletion()) {
            taskCompleted = true;
        }
    }

    bool isTaskCompleted() const { return taskCompleted; }

private:
    bool checkTaskCompletion() {
        // Simulate task completion check
        static int updates = 0;
        return ++updates >= 10;
    }

    bool taskCompleted;
};

int main() {
    try {
        LOG_INFO("Starting Multi-Agent Collaboration Example");

        // Initialize the agent manager
        auto& manager = AgentManager::getInstance();
        if (!manager.configure("config/agents.json")) {
            LOG_ERROR("Failed to configure Agent Manager");
            return 1;
        }

        // Create collaborative agents
        std::vector<std::shared_ptr<CollaborativeAgent>> agents;
        const int numAgents = 3;

        for (int i = 0; i < numAgents; ++i) {
            std::string agentId = "collab_agent_" + std::to_string(i);
            auto agent = std::make_shared<CollaborativeAgent>(agentId, "collaborative");
            agents.push_back(agent);
        }

        // Initialize task environment
        TaskEnvironment environment;

        // Start collaboration simulation
        std::cout << "\nStarting collaborative task...\n";

        int iteration = 0;
        while (!environment.isTaskCompleted() && iteration < 20) {
            // Simulate collaborative behavior
            for (size_t i = 0; i < agents.size(); ++i) {
                // Each agent sends messages to others
                for (size_t j = 0; j < agents.size(); ++j) {
                    if (i != j) {
                        std::string message = "Update_" + std::to_string(iteration);
                        agents[i]->sendMessage(agents[j]->getId(), message);
                        agents[j]->receiveMessage(agents[i]->getId(), message);
                    }
                }

                // Update environment based on agent's action
                std::vector<float> agentData = {
                    static_cast<float>(i),
                    static_cast<float>(iteration),
                    0.5f
                };
                environment.updateState(agents[i]->getId(), agentData);
            }

            // Display iteration status
            std::cout << "\nIteration " << iteration << " completed\n";
            std::cout << "Environment Status: " 
                     << (environment.isTaskCompleted() ? "Task Completed" : "In Progress")
                     << "\n";

            iteration++;
        }

        // Display final results
        std::cout << "\nCollaboration Results:\n";
        std::cout << "Total Iterations: " << iteration << "\n";
        std::cout << "Task Status: " 
                 << (environment.isTaskCompleted() ? "Completed Successfully" : "Not Completed")
                 << "\n";

        LOG_INFO("Multi-Agent Collaboration Example completed successfully");
        return 0;
    }
    catch (const std::exception& e) {
        LOG_ERROR("Example failed: " + std::string(e.what()));
        return 1;
    }
}