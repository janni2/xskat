#include "Preferences.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace Application {

Preferences::Preferences() {}

void Preferences::loadFromFile(const std::string& filename) {
    configFilePath = filename;
    std::ifstream file(filename);
    if (!file.is_open()) {
        // File might not exist on first run, which is fine.
        std::cerr << "Could not open preferences file: " << filename << ". Using defaults." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        if (std::getline(iss, key, '=')) {
            std::string value;
            if (std::getline(iss, value)) {
                // Basic trim for leading/trailing whitespace
                key.erase(0, key.find_first_not_of(" \t"));
                key.erase(key.find_last_not_of(" \t") + 1);
                value.erase(0, value.find_first_not_of(" \t"));
                value.erase(value.find_last_not_of(" \t") + 1);
                settings[key] = value;
            }
        }
    }
}

void Preferences::saveToFile(const std::string& filename) {
    configFilePath = filename;
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open preferences file for writing: " << filename << std::endl;
        return;
    }

    for (const auto& pair : settings) {
        file << pair.first << " = " << pair.second << std::endl;
    }
}

std::string Preferences::getString(const std::string& key, const std::string& defaultValue) const {
    auto it = settings.find(key);
    if (it != settings.end()) {
        return it->second;
    }
    return defaultValue;
}

int Preferences::getInt(const std::string& key, int defaultValue) const {
    auto it = settings.find(key);
    if (it != settings.end()) {
        try {
            return std::stoi(it->second);
        } catch (const std::invalid_argument& ia) {
            std::cerr << "Invalid argument for key '" << key << "': " << it->second << std::endl;
        } catch (const std::out_of_range& oor) {
            std::cerr << "Out of range for key '" << key << "': " << it->second << std::endl;
        }
    }
    return defaultValue;
}

bool Preferences::getBool(const std::string& key, bool defaultValue) const {
    auto it = settings.find(key);
    if (it != settings.end()) {
        if (it->second == "true" || it->second == "1") {
            return true;
        }
        if (it->second == "false" || it->second == "0") {
            return false;
        }
    }
    return defaultValue;
}

void Preferences::setString(const std::string& key, const std::string& value) {
    settings[key] = value;
}

void Preferences::setInt(const std::string& key, int value) {
    settings[key] = std::to_string(value);
}

void Preferences::setBool(const std::string& key, bool value) {
    settings[key] = value ? "true" : "false";
}

} // namespace Application