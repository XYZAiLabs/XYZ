#pragma once

#include <string>
#include <memory>
#include <vector>
#include "../agents/src/base_agent.h"
#include "../agents/src/agent_manager.h"
#include "../agents/src/ai_processor.h"

namespace xyz {

// Forward declarations
class AIModel;

// Public agent interface
class Agent {
public:
    // Factory method
    static std::shared_ptr<Agent> create(const std::string& type, const std::string& id = "");
    
    // Core functionality
    virtual bool initialize() = 0;
    virtual bool start() = 0;
    virtual bool stop() = 0;
    virtual bool pause() = 0;
    virtual bool resume() = 0;

    // Data processing
    virtual bool processData(const std::vector<float>& input) = 0;
    virtual std::vector<float> getOutput() const = 0;

    // State and info
    virtual AgentState getState() const = 0;
    virtual std::string getId() const = 0;
    virtual std::string getType() const = 0;

protected:
    Agent() = default;
    virtual ~Agent() = default;
};

// Public agent manager interface
class AgentSystem {
public:
    static AgentSystem& getInstance();

    virtual bool initialize(const std::string& configPath = "") = 0;
    virtual void shutdown() = 0;
    
    virtual std::shared_ptr<Agent> createAgent(const std::string& type, 
                                             const std::string& id = "") = 0;
    virtual bool destroyAgent(const std::string& id) = 0;
    virtual std::vector<std::string> listAgents() const = 0;
    virtual std::shared_ptr<Agent> getAgent(const std::string& id) = 0;

protected:
    AgentSystem() = default;
    virtual ~AgentSystem() = default;
};

} // namespace xyz