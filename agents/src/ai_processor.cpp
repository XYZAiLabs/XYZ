#include "ai_processor.h"
#include "../../utils/logging.h"

namespace xyz {

bool AIProcessor::initialize(size_t numThreads) {
    if (initialized) {
        LOG_WARNING("AIProcessor already initialized");
        return false;
    }

    shutdownFlag = false;
    
    try {
        for (size_t i = 0; i < numThreads; ++i) {
            workers.emplace_back(&AIProcessor::workerFunction, this);
        }
        
        initialized = true;
        LOG_INFO("AIProcessor initialized with " + std::to_string(numThreads) + " threads");
        return true;
    }
    catch (const std::exception& e) {
        LOG_ERROR("Failed to initialize AIProcessor: " + std::string(e.what()));
        shutdown();
        return false;
    }
}

void AIProcessor::submitTask(const ProcessingTask& task) {
    if (!initialized) {
        LOG_ERROR("Cannot submit task - AIProcessor not initialized");
        return;
    }

    {
        std::lock_guard<std::mutex> lock(queueMutex);
        taskQueue.push(task);
    }
    
    condition.notify_one();
}

void AIProcessor::shutdown() {
    if (!initialized) return;

    {
        std::lock_guard<std::mutex> lock(queueMutex);
        shutdownFlag = true;
    }
    
    condition.notify_all();
    
    for (auto& worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
    
    workers.clear();
    initialized = false;
    LOG_INFO("AIProcessor shutdown complete");
}

AIProcessor::~AIProcessor() {
    shutdown();
}

void AIProcessor::workerFunction() {
    while (true) {
        ProcessingTask task;
        
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            condition.wait(lock, [this] {
                return !taskQueue.empty() || shutdownFlag;
            });
            
            if (shutdownFlag && taskQueue.empty()) {
                return;
            }
            
            if (!taskQueue.empty()) {
                task = std::move(taskQueue.front());
                taskQueue.pop();
            }
        }
        
        try {
            // Process the task and invoke callback
            std::vector<float> result = {1.0f, 2.0f, 3.0f}; // Simulated processing
            task.callback(result);
        }
        catch (const std::exception& e) {
            LOG_ERROR("Error processing task for agent " + task.agentId + ": " + e.what());
        }
    }
}

size_t AIProcessor::getQueueSize() const {
    std::lock_guard<std::mutex> lock(queueMutex);
    return taskQueue.size();
}

size_t AIProcessor::getActiveThreadCount() const {
    return workers.size();
}

} // namespace xyz