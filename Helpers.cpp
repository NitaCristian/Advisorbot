#include <sstream>
#include "Helpers.h"

std::vector<std::string> Helpers::tokenize(std::string line, const std::string &delim) {
    std::vector<std::string> tokens;

    for (char *token = strtok(std::data(line), std::data(delim));
         token != nullptr; token = strtok(nullptr, std::data(delim))) {
        tokens.emplace_back(token);
    }

    return tokens;
}
