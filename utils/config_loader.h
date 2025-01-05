#pragma once

#include <string>
#include <variant>
#include <unordered_map>
#include <memory>
#include "logging.h"

namespace xyz {
namespace utils {

using ConfigValue = std::variant<std::string, int, double, bool>;
using ConfigMap = std::unordered_map<std::string, ConfigValue>;

class ConfigLoader {
public:
    static ConfigLoader& getInstance() {
        static ConfigLoader instance;
        return instance;
    }

    // Configuration loading
    bool loadConfig(const std::string& path);
    bool saveConfig(const std::string& path) const;
    void clear();

    // Value access
    template<typename T>
    T getValue(const std::string& key, const T& defaultValue = T()) const;
    
    bool setValue(const std::string& key, const ConfigValue& value);
    bool hasKey(const std::string& key) const;
    
    // Bulk operations
    ConfigMap getAll() const { return config; }
    bool setAll(const ConfigMap& newConfig);
    
    // Section management
    bool createSection(const std::string& section);
    bool removeSection(const std::string& section);
    ConfigMap getSection(const std::string& section) const;

private:
    ConfigLoader() = default;
    ~ConfigLoader() = default;
    
    ConfigLoader(const ConfigLoader&) = delete;
    ConfigLoader& operator=(const ConfigLoader&) = delete;

    // Internal helpers
    bool parseFile(const std::string& path);
    bool validateConfig() const;
    std::string serializeConfig() const;
    
    // Storage
    ConfigMap config;
    std::unordered_map<std::string, ConfigMap> sections;
};

// Template specializations for getValue
template<>
inline std::string ConfigLoader::getValue<std::string>(
    const std::string& key, const std::string& defaultValue) const {
    auto it = config.find(key);
    if (it != config.end()) {
        try {
            return std::get<std::string>(it->second);
        } catch (const std::bad_variant_access&) {
            LOG_ERROR("Type mismatch for key: " + key);
        }
    }
    return defaultValue;
}

template<>
inline int ConfigLoader::getValue<int>(
    const std::string& key, const int& defaultValue) const {
    auto it = config.find(key);
    if (it != config.end()) {
        try {
            return std::get<int>(it->second);
        } catch (const std::bad_variant_access&) {
            LOG_ERROR("Type mismatch for key: " + key);
        }
    }
    return defaultValue;
}

template<>
inline double ConfigLoader::getValue<double>(
    const std::string& key, const double& defaultValue) const {
    auto it = config.find(key);
    if (it != config.end()) {
        try {
            return std::get<double>(it->second);
        } catch (const std::bad_variant_access&) {
            LOG_ERROR("Type mismatch for key: " + key);
        }
    }
    return defaultValue;
}

template<>
inline bool ConfigLoader::getValue<bool>(
    const std::string& key, const bool& defaultValue) const {
    auto it = config.find(key);
    if (it != config.end()) {
        try {
            return std::get<bool>(it->second);
        } catch (const std::bad_variant_access&) {
            LOG_ERROR("Type mismatch for key: " + key);
        }
    }
    return defaultValue;
}

} // namespace utils
} // namespace xyz