#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "../../utils/logging.h"

namespace xyz {

// Forward declarations
class ModelLoader;

enum class ModelType {
    NEURAL_NETWORK,
    DECISION_TREE,
    RANDOM_FOREST,
    SVM,
    CUSTOM
};

struct ModelConfig {
    std::string name;
    ModelType type;
    std::string version;
    std::unordered_map<std::string, std::string> parameters;
};

class AIModel {
public:
    AIModel(const std::string& modelId, ModelType type);
    virtual ~AIModel() = default;

    // Core model operations
    virtual bool initialize(const ModelConfig& config);
    virtual std::vector<float> inference(const std::vector<float>& input);
    virtual bool train(const std::vector<std::vector<float>>& data);
    virtual bool save(const std::string& path);
    virtual bool load(const std::string& path);

    // Model information
    std::string getModelId() const { return modelId; }
    ModelType getModelType() const { return type; }
    bool isInitialized() const { return initialized; }
    
    // Model configuration
    virtual void setParameter(const std::string& key, const std::string& value);
    virtual std::string getParameter(const std::string& key) const;
    
    // Performance metrics
    struct ModelMetrics {
        double accuracy;
        double latency;
        size_t memoryUsage;
        std::string lastError;
    };
    
    ModelMetrics getMetrics() const { return metrics; }

protected:
    std::string modelId;
    ModelType type;
    bool initialized;
    ModelConfig config;
    ModelMetrics metrics;
    std::unordered_map<std::string, std::string> parameters;

    // Utility methods
    virtual void updateMetrics();
    virtual bool validateInput(const std::vector<float>& input);
};

} // namespace xyz