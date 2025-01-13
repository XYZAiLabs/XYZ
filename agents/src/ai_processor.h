#pragma once

#include <vector>
#include <memory>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "base_agent.h"

namespace xyz {

struct ProcessingTask {
    std::string agentId;
    std::vector<float> data;
    std::function<void(const std::vector<float>&)> callback;
};

class AIProcessor {
public:
    static AIProcessor& getInstance() {
        static AIProcessor instance;
        return instance;
    }

    // Initialize the processor with number of worker threads
    bool initialize(size_t numThreads = std::thread::hardware_concurrency());
    
    // Submit data for processing
    void submitTask(const ProcessingTask& task);
    
    // Shutdown the processor
    void shutdown();

    // Status checks
    bool isInitialized() const { return initialized; }
    size_t getQueueSize() const;
    size_t getActiveThreadCount() const;

private:
    AIProcessor() : initialized(false) {}
    ~AIProcessor();

    // Delete copy constructor and assignment operator
    AIProcessor(const AIProcessor&) = delete;
    AIProcessor& operator=(const AIProcessor&) = delete;

    // Worker thread function
    void workerFunction();

    std::vector<std::thread> workers;
    std::queue<ProcessingTask> taskQueue;
    std::mutex queueMutex;
    std::condition_variable condition;
    bool initialized;
    bool shutdownFlag;
};

} // namespace xyz