#include <gtest/gtest.h>
#include "../agents/src/base_agent.h"
#include "../agents/src/agent_manager.h"
#include "../agents/src/ai_processor.h"

namespace xyz {
namespace tests {

class AgentTest : public ::testing::Test {
protected:
    void SetUp() override {
        manager = &AgentManager::getInstance();
        manager->configure("test_config.json");
    }

    void TearDown() override {
        manager->destroyAllAgents();
    }

    AgentManager* manager;
};

TEST_F(AgentTest, CreateAgent) {
    auto agent = manager->createAgent("test_agent", "agent1");
    ASSERT_NE(agent, nullptr);
    EXPECT_EQ(agent->getId(), "agent1");
    EXPECT_EQ(agent->getState(), AgentState::INITIALIZED);
}

TEST_F(AgentTest, AgentLifecycle) {
    auto agent = manager->createAgent("test_agent", "lifecycle_test");
    ASSERT_NE(agent, nullptr);

    // Test initialization
    EXPECT_TRUE(agent->initialize());
    EXPECT_EQ(agent->getState(), AgentState::INITIALIZED);

    // Test start
    EXPECT_TRUE(agent->start());
    EXPECT_EQ(agent->getState(), AgentState::RUNNING);

    // Test pause
    EXPECT_TRUE(agent->pause());
    EXPECT_EQ(agent->getState(), AgentState::PAUSED);

    // Test resume
    EXPECT_TRUE(agent->resume());
    EXPECT_EQ(agent->getState(), AgentState::RUNNING);

    // Test stop
    EXPECT_TRUE(agent->stop());
    EXPECT_EQ(agent->getState(), AgentState::STOPPED);
}

TEST_F(AgentTest, DataProcessing) {
    auto agent = manager->createAgent("processing_agent", "processor1");
    ASSERT_NE(agent, nullptr);
    
    // Initialize and start agent
    EXPECT_TRUE(agent->initialize());
    EXPECT_TRUE(agent->start());

    // Test data processing
    std::vector<float> input = {1.0f, 2.0f, 3.0f};
    EXPECT_TRUE(agent->processData(input));
    
    auto output = agent->getOutput();
    EXPECT_FALSE(output.empty());
}

TEST_F(AgentTest, AgentManager) {
    // Test multiple agent creation
    for (int i = 0; i < 5; ++i) {
        auto agent = manager->createAgent("test_agent", "agent_" + std::to_string(i));
        ASSERT_NE(agent, nullptr);
    }

    // Test agent listing
    auto agents = manager->listAgents();
    EXPECT_EQ(agents.size(), 5);

    // Test agent retrieval
    auto agent = manager->getAgent("agent_0");
    ASSERT_NE(agent, nullptr);
    EXPECT_EQ(agent->getId(), "agent_0");

    // Test agent destruction
    EXPECT_TRUE(manager->destroyAgent("agent_0"));
    EXPECT_EQ(manager->listAgents().size(), 4);
}

TEST_F(AgentTest, AIProcessor) {
    auto& processor = AIProcessor::getInstance();
    EXPECT_TRUE(processor.initialize(2)); // Initialize with 2 threads

    // Create processing task
    ProcessingTask task{
        "test_agent",
        {1.0f, 2.0f, 3.0f},
        [](const std::vector<float>& result) {
            EXPECT_FALSE(result.empty());
        }
    };

    // Submit task
    processor.submitTask(task);
    
    // Allow time for processing
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Verify processor state
    EXPECT_EQ(processor.getActiveThreadCount(), 2);
    processor.shutdown();
}

} // namespace tests
} // namespace xyz