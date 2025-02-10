#pragma once

#include <string>
#include <memory>
#include <vector>
#include <variant>
#include "../models/src/model.h"
#include "../models/src/model_loader.h"

namespace xyz {

// Public model interface
class Model {
public:
    enum class Type {
        NEURAL_NETWORK,
        DECISION_TREE,
        RANDOM_FOREST,
        SVM,
        CUSTOM
    };

    struct Config {
        std::string name;
        Type type;
        std::string version;
        std::unordered_map<std::string, std::string> parameters;
    };

    struct Metrics {
        double accuracy;
        double latency;
        size_t memoryUsage;
        std::string lastError;
    };

    // Factory method
    static std::shared_ptr<Model> create(const std::string& id, Type type);

    // Core functionality
    virtual bool initialize(const Config& config) = 0;
    virtual std::vector<float> inference(const std::vector<float>& input) = 0;
    virtual bool train(const std::vector<std::vector<float>>& data) = 0;
    
    // Model management
    virtual bool save(const std::string& path) = 0;
    virtual bool load(const std::string& path) = 0;
    
    // Status and metrics
    virtual Metrics getMetrics() const = 0;
    virtual bool isInitialized() const = 0;
    virtual std::string getId() const = 0;
    virtual Type getType() const = 0;

protected:
    Model() = default;
    virtual ~Model() = default;
};

// Public model system interface
class ModelSystem {
public:
    static ModelSystem& getInstance();

    virtual std::shared_ptr<Model> loadModel(const std::string& path) = 0;
    virtual std::shared_ptr<Model> createModel(const std::string& id, Model::Type type) = 0;
    virtual bool unloadModel(const std::string& id) = 0;
    virtual std::vector<std::string> listModels() const = 0;

protected:
    ModelSystem() = default;
    virtual ~ModelSystem() = default;
};

} // namespace xyz