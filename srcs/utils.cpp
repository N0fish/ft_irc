#include "libraries.hpp"

std::vector<std::string> split(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::string temp;
    size_t start = 0, end;

    while ((end = str.find(delimiter, start)) != std::string::npos) {
        temp = str.substr(start, end - start);
        tokens.push_back(temp);
        start = end + 1; 
    }

    tokens.push_back(str.substr(start));

    return tokens;
}