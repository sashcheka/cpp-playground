#include "config.hpp"

#include <sstream>
#include <string>
#include <iostream>
#include <stdexcept>

std::string ParseToken(std::string_view s) {
    // std::size_t l = 0;
    // std::size_t r = s.size();
    // while (l < r && (s[l] == ' ' || s[l] == '\t' || s[l] == '\r')) {
    //     ++l;
    // }

    // while (l < r && (s[r - 1] == ' ' || s[r - 1] == '\t' || s[r - 1] == '\r')) {
    //     --r;
    // }

    std::size_t l = s.find_first_not_of(" \t\r");
    std::size_t r = (l == std::string_view::npos) ? 0 : s.find_last_not_of(" \t\r") + 1;
    if (l == std::string_view::npos) {
        l = r = 0;
    }

    std::string parsed;
    for (std::size_t i = l; i < r; ++i) {
        parsed += s[i];
    }

    return parsed;
}

Config ParseConfig(std::string_view configString) {
    Config config;

    std::istringstream iss;
    iss.str(std::string(configString));
    // or
    // std::istringstream iss{std::string{configString}};
    // or
    // std::istringstream iss{std::string(configString)};
    
    std::string line;

    while (std::getline(iss, line)) {
        std::string tokenLine = ParseToken(line);

        if (tokenLine.empty() || tokenLine[0] == '#') {
            continue;
        }

        std::size_t separatorIdx = line.find('=');
        if (separatorIdx == std::string::npos) {
            throw std::invalid_argument("Config has invalid arguments");
        }

        std::string key = ParseToken(line.substr(0, separatorIdx));
        std::string value = ParseToken(line.substr(separatorIdx + 1));

        config.Set(key, value);
    }

    return config;
}
