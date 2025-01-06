#include "base_agent.h"
#include "../../utils/logging.h"

namespace xyz {

BaseAgent::BaseAgent(const std::string& id, const std::string& type)
    : agentId(id)
    , agentType(type)
    , state(AgentState::INITIALIZED)
{
    LOG_INFO("Creating agent: " + id + " of type: " + type);
}

bool BaseAgent::initialize() {
    if (!aiModel) {
        LOG_ERROR("No AI model loaded for agent: " + agentId);
        return false;
    }

    LOG_INFO("Initializing agent: " + agentId);
    return true;
}

bool BaseAgent::start() {
    if (state != AgentState::INITIALIZED && state != AgentState::STOPPED) {
        LOG_ERROR("Invalid state transition to START for agent: " + agentId);
        return false;
    }

    state = AgentState::RUNNING;
    LOG_INFO("Started agent: " + agentId);
    return true;
}

bool BaseAgent::stop() {
    if (state != AgentState::RUNNING && state != AgentState::PAUSED) {
        LOG_ERROR("Invalid state transition to STOP for agent: " + agentId);
        return false;
    }

    state = AgentState::STOPPED;
    LOG_INFO("Stopped agent: " + agentId);
    return true;
}

bool BaseAgent::pause() {
    if (state != AgentState::RUNNING) {
        LOG_ERROR("Invalid state transition to PAUSE for agent: " + agentId);
        return false;
    }

    state = AgentState::PAUSED;
    LOG_INFO("Paused agent: " + agentId);
    return true;
}

bool BaseAgent::resume() {
    if (state != AgentState::PAUSED) {
        LOG_ERROR("Invalid state transition to RESUME for agent: " + agentId);
        return false;
    }

    state = AgentState::RUNNING;
    LOG_INFO("Resumed agent: " + agentId);
    return true;
}

bool BaseAgent::processData(const std::vector<float>& input) {
    if (state != AgentState::RUNNING) {
        LOG_ERROR("Cannot process data - agent not running: " + agentId);
        return false;
    }

    try {
        lastOutput = aiModel->inference(input);
        return true;
    } catch (const std::exception& e) {
        LOG_ERROR("Error processing data in agent " + agentId + ": " + e.what());
        state = AgentState::ERROR;
        return false;
    }
}

std::vector<float> BaseAgent::getOutput() const {
    return lastOutput;
}

bool BaseAgent::loadModel(std::shared_ptr<AIModel> model) {
    if (!model) {
        LOG_ERROR("Attempted to load null model in agent: " + agentId);
        return false;
    }

    aiModel = model;
    LOG_INFO("Loaded AI model in agent: " + agentId);
    return true;
}

void BaseAgent::setConfiguration(const std::unordered_map<std::string, std::string>& config) {
    configuration = config;
    LOG_INFO("Updated configuration for agent: " + agentId);
}

} // namespace xyz