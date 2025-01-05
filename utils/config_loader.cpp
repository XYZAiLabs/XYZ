#include "config_loader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <regex>

namespace xyz {
namespace utils {

bool ConfigLoader::loadConfig(const std::string& path) {
    try {
        if (!std::filesystem::exists(path)) {
            LOG_ERROR("Config file not found: " + path);
            return false;
        }

        if (!parseFile(path)) {
            LOG_ERROR("Failed to parse config file: " + path);
            return false;
        }

        if (!validateConfig()) {
            LOG_ERROR("Invalid configuration in file: " + path);
            return false;
        }

        LOG_INFO("Successfully loaded configuration from: " + path);
        return true;
    }
    catch (const std::exception& e) {
        LOG_ERROR("Error loading config: " + std::string(e.what()));
        return false;
    }
}

bool ConfigLoader::parseFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        LOG_ERROR("Unable to open config file: " + path);
        return false;
    }

    std::string line;
    std::string currentSection;
    const std::regex sectionRegex(R"(\[(.*?)\])");
    const std::regex keyValueRegex(R"((\w+)\s*=\s*(.*))");

    while (std::getline(file, line)) {
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }

        // Trim whitespace
        line = std::regex_replace(line, std::regex("^\\s+|\\s+$"), "");

        // Check for section header
        std::smatch sectionMatch;
        if (std::regex_match(line, sectionMatch, sectionRegex)) {
            currentSection = sectionMatch[1].str();
            if (!sections.contains(currentSection)) {
                sections[currentSection] = ConfigMap();
            }
            continue;
        }

        // Parse key-value pairs
        std::smatch kvMatch;
        if (std::regex_match(line, kvMatch, keyValueRegex)) {
            std::string key = kvMatch[1].str();
            std::string value = kvMatch[2].str();

            // Parse the value based on type
            ConfigValue configValue;
            if (value == "true" || value == "false") {
                configValue = (value == "true");
            }
            else if (std::regex_match(value, std::regex(R"(-?\d+)"))) {
                configValue = std::stoi(value);
            }
            else if (std::regex_match(value, std::regex(R"(-?\d*\.?\d+)"))) {
                configValue = std::stod(value);
            }
            else {
                // Remove quotes if present
                value = std::regex_replace(value, std::regex("^\"|\"$"), "");
                configValue = value;
            }

            // Store in appropriate map
            if (currentSection.empty()) {
                config[key] = configValue;
            } else {
                sections[currentSection][key] = configValue;
            }
        }
    }

    return true;
}

bool ConfigLoader::saveConfig(const std::string& path) const {
    try {
        std::ofstream file(path);
        if (!file.is_open()) {
            LOG_ERROR("Failed to open config file for writing: " + path);
            return false;
        }

        // Write main configuration
        file << "# XYZ Framework Configuration\n\n";
        for (const auto& [key, value] : config) {
            file << key << " = ";
            std::visit([&file](const auto& v) {
                if constexpr (std::is_same_v<std::string, std::decay_t<decltype(v)>>) {
                    file << "\"" << v << "\"";
                } else {
                    file << v;
                }
            }, value);
            file << "\n";
        }

        // Write sections
        for (const auto& [section, sectionConfig] : sections) {
            file << "\n[" << section << "]\n";
            for (const auto& [key, value] : sectionConfig) {
                file << key << " = ";
                std::visit([&file](const auto& v) {
                    if constexpr (std::is_same_v<std::string, std::decay_t<decltype(v)>>) {
                        file << "\"" << v << "\"";
                    } else {
                        file << v;
                    }
                }, value);
                file << "\n";
            }
        }

        LOG_INFO("Successfully saved configuration to: " + path);
        return true;
    }
    catch (const std::exception& e) {
        LOG_ERROR("Error saving config: " + std::string(e.what()));
        return false;
    }
}

void ConfigLoader::clear() {
    config.clear();
    sections.clear();
    LOG_INFO("Configuration cleared");
}

bool ConfigLoader::setValue(const std::string& key, const ConfigValue& value) {
    try {
        config[key] = value;
        LOG_DEBUG("Set config value for key: " + key);
        return true;
    }
    catch (const std::exception& e) {
        LOG_ERROR("Error setting config value: " + std::string(e.what()));
        return false;
    }
}

bool ConfigLoader::hasKey(const std::string& key) const {
    return config.find(key) != config.end();
}

bool ConfigLoader::setAll(const ConfigMap& newConfig) {
    try {
        config = newConfig;
        LOG_INFO("Updated all configuration values");
        return true;
    }
    catch (const std::exception& e) {
        LOG_ERROR("Error updating configuration: " + std::string(e.what()));
        return false;
    }
}

bool ConfigLoader::createSection(const std::string& section) {
    if (sections.find(section) != sections.end()) {
        LOG_WARNING("Section already exists: " + section);
        return false;
    }

    sections[section] = ConfigMap();
    LOG_INFO("Created new config section: " + section);
    return true;
}

bool ConfigLoader::removeSection(const std::string& section) {
    auto it = sections.find(section);
    if (it == sections.end()) {
        LOG_WARNING("Section not found: " + section);
        return false;
    }

    sections.erase(it);
    LOG_INFO("Removed config section: " + section);
    return true;
}

ConfigMap ConfigLoader::getSection(const std::string& section) const {
    auto it = sections.find(section);
    if (it == sections.end()) {
        LOG_WARNING("Section not found: " + section);
        return ConfigMap();
    }
    return it->second;
}

bool ConfigLoader::validateConfig() const {
    // Check for required keys
    const std::vector<std::string> requiredKeys = {
        "version",
        "log_level",
        "max_agents"
    };

    for (const auto& key : requiredKeys) {
        if (!hasKey(key)) {
            LOG_ERROR("Missing required configuration key: " + key);
            return false;
        }
    }

    // Validate version format
    try {
        std::string version = getValue<std::string>("version");
        if (!std::regex_match(version, std::regex(R"(\d+\.\d+\.\d+)"))) {
            LOG_ERROR("Invalid version format: " + version);
            return false;
        }
    }
    catch (...) {
        LOG_ERROR("Error validating version format");
        return false;
    }

    return true;
}

} // namespace utils
} // namespace xyz