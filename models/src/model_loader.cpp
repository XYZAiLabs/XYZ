#include "model_loader.h"
#include <fstream>
#include "../../utils/logging.h"

namespace xyz {

std::shared_ptr<AIModel> ModelLoader::loadModel(const std::string& path) {
    try {
        if (!validateModelPath(path)) {
            LOG_ERROR("Invalid model path: " + path);
            return nullptr;
        }

        // Parse model configuration
        auto config = parseModelConfig(path);
        
        // Create new model instance
        auto model = createModel(config.name, config.type);
        if (!model) {
            LOG_ERROR("Failed to create model instance");
            return nullptr;
        }

        // Initialize and load model data
        if (!model->initialize(config)) {
            LOG_ERROR("Failed to initialize model: " + config.name);
            return nullptr;
        }

        if (!model->load(path)) {
            LOG_ERROR("Failed to load model data: " + config.name);
            return nullptr;
        }

        // Register model
        if (!registerModel(config.name, model)) {
            LOG_ERROR("Failed to register model: " + config.name);
            return nullptr;
        }

        LOG_INFO("Successfully loaded model: " + config.name);
        return model;
    }
    catch (const std::exception& e) {
        LOG_ERROR("Error loading model: " + std::string(e.what()));
        return nullptr;
    }
}

std::shared_ptr<AIModel> ModelLoader::createModel(const std::string& modelId, ModelType type) {
    try {
        auto model = std::make_shared<AIModel>(modelId, type);
        LOG_INFO("Created new model instance: " + modelId);
        return model;
    }
    catch (const std::exception& e) {
        LOG_ERROR("Failed to create model: " + std::string(e.what()));
        return nullptr;
    }
}

bool ModelLoader::registerModel(const std::string& modelId, std::shared_ptr<AIModel> model) {
    if (!model) {
        LOG_ERROR("Cannot register null model");
        return false;
    }

    auto [it, success] = models.insert({modelId, model});
    if (!success) {
        LOG_ERROR("Model already registered: " + modelId);
        return false;
    }

    LOG_INFO("Registered model: " + modelId);
    return true;
}

bool ModelLoader::unregisterModel(const std::string& modelId) {
    auto it = models.find(modelId);
    if (it == models.end()) {
        LOG_ERROR("Model not found: " + modelId);
        return false;
    }

    models.erase(it);
    LOG_INFO("Unregistered model: " + modelId);
    return true;
}

std::shared_ptr<AIModel> ModelLoader::getModel(const std::string& modelId) {
    auto it = models.find(modelId);
    if (it == models.end()) {
        LOG_ERROR("Model not found: " + modelId);
        return nullptr;
    }
    return it->second;
}

std::vector<std::string> ModelLoader::listModels() const {
    std::vector<std::string> modelIds;
    modelIds.reserve(models.size());
    for (const auto& [id, _] : models) {
        modelIds.push_back(id);
    }
    return modelIds;
}

void ModelLoader::clearModels() {
    models.clear();
    LOG_INFO("Cleared all models");
}

bool ModelLoader::validateModelPath(const std::string& path) {
    // Simulate path validation
    return !path.empty();
}

ModelConfig ModelLoader::parseModelConfig(const std::string& path) {
    // Simulate config parsing
    ModelConfig config;
    config.name = "model_" + std::to_string(models.size() + 1);
    config.type = ModelType::NEURAL_NETWORK;
    config.version = "1.0.0";
    return config;
}

} // namespace xyz