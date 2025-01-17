#pragma once

#include <string>
#include <memory>
#include "model.h"

namespace xyz {

class ModelLoader {
public:
    static ModelLoader& getInstance() {
        static ModelLoader instance;
        return instance;
    }

    // Model loading functions
    std::shared_ptr<AIModel> loadModel(const std::string& path);
    std::shared_ptr<AIModel> createModel(const std::string& modelId, ModelType type);
    
    // Model registration
    bool registerModel(const std::string& modelId, std::shared_ptr<AIModel> model);
    bool unregisterModel(const std::string& modelId);
    
    // Model management
    std::shared_ptr<AIModel> getModel(const std::string& modelId);
    std::vector<std::string> listModels() const;
    void clearModels();

private:
    ModelLoader() = default;
    ~ModelLoader() = default;
    
    ModelLoader(const ModelLoader&) = delete;
    ModelLoader& operator=(const ModelLoader&) = delete;

    // Helper functions
    bool validateModelPath(const std::string& path);
    ModelConfig parseModelConfig(const std::string& path);
    
    // Storage for loaded models
    std::unordered_map<std::string, std::shared_ptr<AIModel>> models;
};

} // namespace xyz