#include "Level.hpp"

using namespace eng;

Level::Level(std::vector<std::string> lines)
{
    this->_index = 0;
    this->_speedRead = 1;
    std::smatch match;

    for (std::size_t i = 0; i < lines.size(); i++) {
        if (i == 0 && std::regex_match(lines[i], std::regex("^//.*"))) {
            std::regex_search(lines[i], match, std::regex(".*gap:([0-9]+(\\.[0-9]+)?)"));
            this->_speedRead = std::stof(match[1]);
            continue;
        }
    }
    std::cout << this->_speedRead << std::endl;
    std::cout << "----------------" << std::endl;
}