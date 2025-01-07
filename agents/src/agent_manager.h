#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include "base_agent.h"
#include "../../utils/logging.h"

namespace xyz {

class AgentManager {
public:
    static AgentManager& getInstance() {
        static AgentManager instance;
        return instance;
    }

    // Agent lifecycle management
    std::shared_ptr<BaseAgent> createAgent(const std::string& type, const std::string& id = "");
    bool destroyAgent(const std::string& agentId);
    std::shared_ptr<BaseAgent> getAgent(const std::string& agentId);
    std::vector<std::string> listAgents() const;

    // Batch operations
    bool startAllAgents();
    bool stopAllAgents();
    void destroyAllAgents();

    // Configuration
    bool configure(const std::string& configPath);
    bool isInitialized() const { return initialized; }

private:
    AgentManager() : initialized(false) {}
    ~AgentManager() = default;

    AgentManager(const AgentManager&) = delete;
    AgentManager& operator=(const AgentManager&) = delete;

    std::unordered_map<std::string, std::shared_ptr<BaseAgent>> agents;
    bool initialized;
    std::string generateAgentId() const;
};

} // namespace xyz