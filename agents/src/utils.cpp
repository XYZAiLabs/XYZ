#include "utils.h"
#include <sstream>
#include <json/json.h>
#include "../../utils/logging.h"

namespace xyz {
namespace agent_utils {

bool validateAgentConfig(const AgentConfig& config) {
    if (config.type.empty()) {
        LOG_ERROR("Agent type cannot be empty");
        return false;
    }
    
    if (config.modelPath.empty()) {
        LOG_ERROR("Model path cannot be empty");
        return false;
    }
    
    return true;
}

std::string serializeAgentState(const std::unordered_map<std::string, std::string>& state) {
    Json::Value root;
    for (const auto& pair : state) {
        root[pair.first] = pair.second;
    }
    
    Json::FastWriter writer;
    return writer.write(root);
}

std::unordered_map<std::string, std::string> deserializeAgentState(const std::string& serialized) {
    std::unordered_map<std::string, std::string> state;
    
    Json::Value root;
    Json::Reader reader;
    
    if (!reader.parse(serialized, root)) {
        LOG_ERROR("Failed to parse serialized state");
        return state;
    }
    
    for (const auto& memberName : root.getMemberNames()) {
        state[memberName] = root[memberName].asString();
    }
    
    return state;
}

// Static storage for metrics
static std::unordered_map<std::string, AgentMetrics> agentMetrics;
static std::mutex metricsLock;

void MetricsCollector::recordMetrics(const std::string& agentId, const AgentMetrics& metrics) {
    std::lock_guard<std::mutex> lock(metricsLock);
    agentMetrics[agentId] = metrics;
}

AgentMetrics MetricsCollector::getMetrics(const std::string& agentId) {
    std::lock_guard<std::mutex> lock(metricsLock);
    auto it = agentMetrics.find(agentId);
    if (it != agentMetrics.end()) {
        return it->second;
    }
    return AgentMetrics{};
}

void MetricsCollector::clearMetrics(const std::string& agentId) {
    std::lock_guard<std::mutex> lock(metricsLock);
    agentMetrics.erase(agentId);
}

} // namespace agent_utils
} // namespace xyz