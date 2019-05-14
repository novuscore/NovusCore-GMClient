#pragma once
#include "../Libraries/json/json.hpp"
#include <iostream>
#include <sstream>

using json = nlohmann::json;
class ConfigHandler
{
public:
    static bool Load(std::string configFileName)
    {
        _configFileName = configFileName;
        
        FILE* configFile = nullptr;
        fopen_s(&configFile, _configFileName.c_str(), "r");

        if (!configFile)
        {
            printf("Could not find '%s' in directory. Press a key to exit.\n", _configFileName.c_str());
            return false;
        }

        std::stringstream fileStringStream;
        char buffer[128];

        while (!feof(configFile))
        {
            if (fgets(buffer, 128, configFile) == NULL) break;
            fileStringStream << buffer;
        }
        fclose(configFile);

        std::string output = fileStringStream.str();
        if (output.size() == 0)
        {
            printf("Failed to initialize config file, found 0 configurations.\n");
            return false;
        }

        ConfigFile = json::parse(output.begin(), output.end());
        printf("Loaded config file: '%s'\n", _configFileName.c_str());
        return true;
    }

    ~ConfigHandler() {}
    static json ConfigFile;
private:
    ConfigHandler() {} // Constructor is private because we don't want to allow newing these

    static std::string _configFileName;
};

std::string ConfigHandler::_configFileName;
json ConfigHandler::ConfigFile;