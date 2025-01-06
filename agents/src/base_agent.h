#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include "../../models/src/model.h"
#include "../../utils/logging.h"

namespace xyz {

enum class AgentState {
    INITIALIZED,
    RUNNING,
    PAUSED,
    STOPPED,
    ERROR
};

class BaseAgent {
public:
    BaseAgent(const std::string& id, const std::string& type);
    virtual ~BaseAgent() = default;

    // Core agent functionality
    virtual bool initialize();
    virtual bool start();
    virtual bool stop();
    virtual bool pause();
    virtual bool resume();

    // State management
    AgentState getState() const { return state; }
    const std::string& getId() const { return agentId; }
    const std::string& getType() const { return agentType; }

    // Data processing
    virtual bool processData(const std::vector<float>& input);
    virtual std::vector<float> getOutput() const;

    // Model management
    bool loadModel(std::shared_ptr<AIModel> model);
    void setConfiguration(const std::unordered_map<std::string, std::string>& config);

protected:
    std::string agentId;
    std::string agentType;
    AgentState state;
    std::shared_ptr<AIModel> aiModel;
    std::unordered_map<std::string, std::string> configuration;
    std::vector<float> lastOutput;
};

} // namespace xyz