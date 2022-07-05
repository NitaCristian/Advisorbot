#pragma once

#include <vector>
#include <string>
#include <cstring>

class Helpers {
public:
    /**
     * Tokenizer function to split an input string into tokens separated by delimiters
     * @param line Input string
     * @param delim String containing delimiters
    */
    static std::vector<std::string> tokenize(std::string line, const std::string &delim);
};