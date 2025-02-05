#include <iostream>
#include <chrono>
#include <thread>
#include "../../agents/src/agent_manager.h"
#include "../../agents/src/ai_processor.h"
#include "../../utils/logging.h"

// Example 1: Real-time Data Processing with Multiple Agents
// This example demonstrates how to set up multiple agents for processing 
// streaming data with real-time feedback.

using namespace xyz;

// Simulated sensor data generator
class SensorDataGenerator {
public:
    static std::vector<float> generateData() {
        static float t = 0.0f;
        std::vector<float> data = {
            std::sin(t),                    // Simulated temperature
            std::cos(t * 0.5f),            // Simulated pressure
            std::sin(t * 0.3f) * 0.5f      // Simulated humidity
        };
        t += 0.1f;
        return data;
    }
};

// Callback for processing results
void processResults(const std::string& agentId, const std::vector<float>& results) {
    std::cout << "Agent " << agentId << " processed data:\n";
    std::cout << "  - Normalized temperature: " << results[0] << "\n";
    std::cout << "  - Pressure threshold: " << (results[1] > 0.5f ? "HIGH" : "LOW") << "\n";
    std::cout << "  - Humidity status: " << results[2] << "\n";
}

int main() {
    try {
        LOG_INFO("Starting Real-time Data Processing Example");

        // Initialize the agent manager
        auto& manager = AgentManager::getInstance();
        if (!manager.configure("config/agents.json")) {
            LOG_ERROR("Failed to configure Agent Manager");
            return 1;
        }

        // Create multiple agents for different processing tasks
        auto tempAgent = manager.createAgent("temperature_processor", "temp_agent");
        auto pressureAgent = manager.createAgent("pressure_processor", "pressure_agent");
        auto humidityAgent = manager.createAgent("humidity_processor", "humidity_agent");

        if (!tempAgent || !pressureAgent || !humidityAgent) {
            LOG_ERROR("Failed to create all required agents");
            return 1;
        }

        // Start all agents
        tempAgent->start();
        pressureAgent->start();
        humidityAgent->start();

        // Initialize the AI processor
        auto& processor = AIProcessor::getInstance();
        processor.initialize(3); // Use 3 worker threads

        // Main processing loop
        int iterations = 0;
        while (iterations < 100) { // Process 100 data points
            // Generate simulated sensor data
            auto sensorData = SensorDataGenerator::generateData();

            // Submit processing tasks for each agent
            ProcessingTask tempTask{
                "temp_agent",
                {sensorData[0]},
                [](const auto& result) { processResults("temp_agent", result); }
            };
            processor.submitTask(tempTask);

            ProcessingTask pressureTask{
                "pressure_agent",
                {sensorData[1]},
                [](const auto& result) { processResults("pressure_agent", result); }
            };
            processor.submitTask(pressureTask);

            ProcessingTask humidityTask{
                "humidity_agent",
                {sensorData[2]},
                [](const auto& result) { processResults("humidity_agent", result); }
            };
            processor.submitTask(humidityTask);

            // Simulate real-time data interval
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            iterations++;

            // Display system status every 10 iterations
            if (iterations % 10 == 0) {
                std::cout << "\nSystem Status:\n";
                std::cout << "Queue Size: " << processor.getQueueSize() << "\n";
                std::cout << "Active Threads: " << processor.getActiveThreadCount() << "\n";
                std::cout << "Iterations: " << iterations << "/100\n\n";
            }
        }

        // Cleanup
        manager.destroyAllAgents();
        processor.shutdown();

        LOG_INFO("Real-time Data Processing Example completed successfully");
        return 0;
    }
    catch (const std::exception& e) {
        LOG_ERROR("Example failed: " + std::string(e.what()));
        return 1;
    }
}