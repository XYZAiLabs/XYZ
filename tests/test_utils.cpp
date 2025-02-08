#include <gtest/gtest.h>
#include "../utils/logging.h"
#include "../utils/config_loader.h"
#include "../utils/constants.h"

namespace xyz {
namespace tests {

class UtilsTest : public ::testing::Test {
protected:
    void SetUp() override {
        logger = &utils::Logger::getInstance();
        config = &utils::ConfigLoader::getInstance();
    }

    utils::Logger* logger;
    utils::ConfigLoader* config;
};

TEST_F(UtilsTest, LoggingBasic) {
    // Test different log levels
    LOG_INFO("Test info message");
    LOG_DEBUG("Test debug message");
    LOG_WARNING("Test warning message");
    LOG_ERROR("Test error message");
    
    // Test file logging
    logger->setLogFile("test.log");
    logger->enableFileOutput(true);
    LOG_INFO("Test file logging");
    
    // Verify log file exists and contains content
    std::ifstream logFile("test.log");
    EXPECT_TRUE(logFile.good());
    std::string line;
    std::getline(logFile, line);
    EXPECT_FALSE(line.empty());
}

TEST_F(UtilsTest, ConfigLoaderBasic) {
    // Test config value setting and getting
    config->setValue("test_string", std::string("value"));
    config->setValue("test_int", 42);
    config->setValue("test_double", 3.14);
    config->setValue("test_bool", true);

    EXPECT_EQ(config->getValue<std::string>("test_string"), "value");
    EXPECT_EQ(config->getValue<int>("test_int"), 42);
    EXPECT_DOUBLE_EQ(config->getValue<double>("test_double"), 3.14);
    EXPECT_TRUE(config->getValue<bool>("test_bool"));
}

TEST_F(UtilsTest, ConfigLoaderFile) {
    // Create test config file
    std::ofstream testConfig("test_config.txt");
    testConfig << "string_value = \"test\"\n";
    testConfig << "int_value = 123\n";
    testConfig << "double_value = 3.14\n";
    testConfig << "bool_value = true\n";
    testConfig << "\n[section1]\n";
    testConfig << "key1 = \"value1\"\n";
    testConfig.close();

    // Test loading
    EXPECT_TRUE(config->loadConfig("test_config.txt"));
    
    // Verify values
    EXPECT_EQ(config->getValue<std::string>("string_value"), "test");
    EXPECT_EQ(config->getValue<int>("int_value"), 123);
    EXPECT_DOUBLE_EQ(config->getValue<double>("double_value"), 3.14);
    EXPECT_TRUE(config->getValue<bool>("bool_value"));

    // Test section handling
    auto section = config->getSection("section1");
    EXPECT_FALSE(section.empty());
    EXPECT_EQ(std::get<std::string>(section["key1"]), "value1");
}

TEST_F(UtilsTest, Constants) {
    // Test version constants
    EXPECT_GT(constants::VERSION_MAJOR, 0);
    EXPECT_GE(constants::VERSION_MINOR, 0);
    EXPECT_GE(constants::VERSION_PATCH, 0);
    
    // Test system limits
    EXPECT_GT(constants::MAX_AGENTS, 0);
    EXPECT_GT(constants::MAX_MODELS, 0);
    EXPECT_GT(constants::MAX_CONNECTIONS, 0);
    
    // Test memory limits
    EXPECT_GT(constants::MAX_MEMORY_PER_AGENT, 0);
    EXPECT_GT(constants::MAX_TOTAL_MEMORY, 0);
    
    // Test error codes
    EXPECT_EQ(static_cast<int>(constants::ErrorCode::SUCCESS), 0);
}

} // namespace tests
} // namespace xyz