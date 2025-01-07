#include "agent_manager.h"
#include <random>
#include <sstream>
#include "../../utils/config_loader.h"

namespace xyz {

std::shared_ptr<BaseAgent> AgentManager::createAgent(const std::string& type, const std::string& id) {
    std::string agentId = id.empty() ? generateAgentId() : id;
    
    if (agents.find(agentId) != agents.end()) {
        LOG_ERROR("Agent ID already exists: " + agentId);
        return nullptr;
    }
    
    try {
        auto agent = std::make_shared<BaseAgent>(agentId, type);
        if (!agent->initialize()) {
            LOG_ERROR("Failed to initialize agent: " + agentId);
            return nullptr;
        }
        
        agents[agentId] = agent;
        LOG_INFO("Created agent: " + agentId + " of type: " + type);
        return agent;
    }
    catch (const std::exception& e) {
        LOG_ERROR("Error creating agent: " + std::string(e.what()));
        return nullptr;
    }
}

bool AgentManager::destroyAgent(const std::string& agentId) {
    auto it = agents.find(agentId);
    if (it == agents.end()) {
        LOG_ERROR("Agent not found: " + agentId);
        return false;
    }
    
    try {
        it->second->stop();
        agents.erase(it);
        LOG_INFO("Destroyed agent: " + agentId);
        return true;
    }
    catch (const std::exception& e) {
        LOG_ERROR("Error destroying agent: " + agentId + ": " + e.what());
        return false;
    }
}

std::shared_ptr<BaseAgent> AgentManager::getAgent(const std::string& agentId) {
    auto it = agents.find(agentId);
    if (it == agents.end()) {
        return nullptr;
    }
    return it->second;
}

std::vector<std::string> AgentManager::listAgents() const {
    std::vector<std::string> agentIds;
    for (const auto& pair : agents) {
        agentIds.push_back(pair.first);
    }
    return agentIds;
}

bool AgentManager::startAllAgents() {
    bool success = true;
    for (const auto& pair : agents) {
        if (!pair.second->start()) {
            LOG_ERROR("Failed to start agent: " + pair.first);
            success = false;
        }
    }
    return success;
}

bool AgentManager::stopAllAgents() {
    bool success = true;
    for (const auto& pair : agents) {
        if (!pair.second->stop()) {
            LOG_ERROR("Failed to stop agent: " + pair.first);
            success = false;
        }
    }
    return success;
}

void AgentManager::destroyAllAgents() {
    stopAllAgents();
    agents.clear();
    LOG_INFO("All agents destroyed");
}

bool AgentManager::configure(const std::string& configPath) {
    try {
        // Simulated configuration loading
        initialized = true;
        LOG_INFO("Agent manager configured successfully");
        return true;
    }
    catch (const std::exception& e) {
        LOG_ERROR("Failed to configure agent manager: " + std::string(e.what()));
        return false;
    }
}

std::string AgentManager::generateAgentId() const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1000, 9999);
    
    std::stringstream ss;
    ss << "agent_" << dis(gen);
    return ss.str();
}

} // namespace xyz