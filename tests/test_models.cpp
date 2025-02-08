#include <gtest/gtest.h>
#include "../models/src/model.h"
#include "../models/src/model_loader.h"

namespace xyz {
namespace tests {

class ModelTest : public ::testing::Test {
protected:
    void SetUp() override {
        loader = &ModelLoader::getInstance();
    }

    void TearDown() override {
        loader->clearModels();
    }

    ModelLoader* loader;
};

TEST_F(ModelTest, ModelCreation) {
    auto model = std::make_shared<AIModel>("test_model", ModelType::NEURAL_NETWORK);
    ASSERT_NE(model, nullptr);
    EXPECT_EQ(model->getModelId(), "test_model");
    EXPECT_EQ(model->getModelType(), ModelType::NEURAL_NETWORK);
}

TEST_F(ModelTest, ModelInitialization) {
    auto model = std::make_shared<AIModel>("init_test", ModelType::NEURAL_NETWORK);
    
    ModelConfig config;
    config.name = "test_model";
    config.type = ModelType::NEURAL_NETWORK;
    config.version = "1.0.0";
    config.parameters["layers"] = "3";
    
    EXPECT_TRUE(model->initialize(config));
    EXPECT_TRUE(model->isInitialized());
}

TEST_F(ModelTest, ModelInference) {
    auto model = std::make_shared<AIModel>("inference_test", ModelType::NEURAL_NETWORK);
    
    // Initialize model
    ModelConfig config;
    config.name = "inference_model";
    config.type = ModelType::NEURAL_NETWORK;
    EXPECT_TRUE(model->initialize(config));

    // Test inference
    std::vector<float> input = {1.0f, 2.0f, 3.0f};
    auto output = model->inference(input);
    
    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output.size(), input.size());
}

TEST_F(ModelTest, ModelLoader) {
    // Test model loading
    auto model = loader->loadModel("test_model.json");
    ASSERT_NE(model, nullptr);
    
    // Test model registration
    EXPECT_TRUE(loader->registerModel("test_model", model));
    
    // Test model retrieval
    auto retrievedModel = loader->getModel("test_model");
    ASSERT_NE(retrievedModel, nullptr);
    EXPECT_EQ(retrievedModel->getModelId(), "test_model");
    
    // Test model listing
    auto models = loader->listModels();
    EXPECT_EQ(models.size(), 1);
    EXPECT_EQ(models[0], "test_model");
}

TEST_F(ModelTest, ModelPerformance) {
    auto model = std::make_shared<AIModel>("perf_test", ModelType::NEURAL_NETWORK);
    model->initialize(ModelConfig{});
    
    // Test inference performance
    const int numIterations = 1000;
    std::vector<float> input = {1.0f, 2.0f, 3.0f};
    
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i) {
        model->inference(input);
    }
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    auto metrics = model->getMetrics();
    
    EXPECT_GT(metrics.accuracy, 0.0);
    EXPECT_GT(metrics.latency, 0.0);
}

} // namespace tests
} // namespace xyz