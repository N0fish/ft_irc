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

std::string joinArgs(const std::vector<std::string> &args, size_t startIndex) {
    std::string result;
    
    for (size_t i = startIndex; i < args.size(); i++) {
        if (i != startIndex) // Ajouter un espace sauf pour le premier mot
            result += " ";
        result += args[i];
    }

    // Supprimer le ":" au début si présent
    if (!result.empty() && result[0] == ':')
        result.erase(0, 1);

    return result;
}
