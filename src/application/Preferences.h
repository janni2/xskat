#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <string>
#include <map>

namespace Application {

class Preferences {
public:
    Preferences();

    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename);

    std::string getString(const std::string& key, const std::string& defaultValue) const;
    int getInt(const std::string& key, int defaultValue) const;
    bool getBool(const std::string& key, bool defaultValue) const;

    void setString(const std::string& key, const std::string& value);
    void setInt(const std::string& key, int value);
    void setBool(const std::string& key, bool value);

private:
    std::map<std::string, std::string> settings;
    std::string configFilePath;
};

} // namespace Application

#endif // PREFERENCES_H