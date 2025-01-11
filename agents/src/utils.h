#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace xyz {
namespace agent_utils {

// Agent configuration utilities
struct AgentConfig {
    std::string type;
    std::string modelPath;
    std::unordered_map<std::string, std::string> parameters;
};

// Utility functions
bool validateAgentConfig(const AgentConfig& config);
std::string serializeAgentState(const std::unordered_map<std::string, std::string>& state);
std::unordered_map<std::string, std::string> deserializeAgentState(const std::string& serialized);

// Performance monitoring
struct AgentMetrics {
    double processingTime;
    size_t memoryUsage;
    size_t dataProcessed;
    double accuracy;
};

class MetricsCollector {
public:
    static void recordMetrics(const std::string& agentId, const AgentMetrics& metrics);
    static AgentMetrics getMetrics(const std::string& agentId);
    static void clearMetrics(const std::string& agentId);
};

} // namespace agent_utils
} // namespace xyz