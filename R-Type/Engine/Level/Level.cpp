#include "Level.hpp"

using namespace eng;

Level::Level(std::vector<std::string> lines)
{
    this->_index = 0;
    this->_speedRead = 1;
    this->_delayRead = 0;
    this->_charPerScreen = 1;
    std::smatch match;

    if (std::regex_match(lines[0], std::regex("^//.*"))) {
        if (std::regex_search(lines[0], match, std::regex(".*speedRead:([0-9]+(\\.[0-9]+)?)")))
            this->_speedRead = std::stof(match[1]);
        if (std::regex_search(lines[0], match, std::regex(".*charPerScreen:([0-9]+(\\.[0-9]+)?)")))
            this->_charPerScreen = 1920 / std::stoi(match[1]);
        lines.erase(lines.begin());
    }
    for (std::size_t i = 0; i < lines.size();) {
        if (std::regex_match(lines[i], std::regex("^--.*"))) {
            lines.erase(lines.begin() + i);
            continue;
        }
        lines[i].erase(std::remove(lines[i].begin(), lines[i].end(), '-'), lines[i].end());
        i++;
    }
    for (std::size_t i = 0; i < lines[0].size(); i++) {
        for (std::size_t j = 0; j < lines.size(); j++) {
            switch (lines[j][i]) {
            case 'E':
                this->_level += "E(" + std::to_string(static_cast<int>(i * this->_charPerScreen)) + ":" + std::to_string(1080 / lines.size() * j) + ")";
                break;
            case 'B':
                this->_level += "B(" + std::to_string(static_cast<int>(i * this->_charPerScreen)) + ":" + std::to_string(1080 / lines.size() * j) + ")";
                break;
            case 'D':
                this->_level += "D(" + std::to_string(static_cast<int>(i * this->_charPerScreen)) + ":" + std::to_string(1080 / lines.size() * j) + ")";
                break;
            default:
                this->_level += "";
                break;
            }
        }
        this->_level += "|";
    }
}

void Level::parseLevel()
{
    if (this->_level[this->_index] == '|') {
        this->_index++;
        return;
    }
    std::smatch match;
    std::string levelStr(this->_level.substr(this->_index));
    if (std::regex_search(levelStr, match, std::regex("([A-Z])\\(([0-9]+):([0-9]+)\\)"))) {
        this->_index += match[0].length();
        switch (match[1].str()[0]) {
        case 'E':
            std::cout << std::stoi(match[2]) << " " << std::stoi(match[3]) << std::endl;
            break;
        case 'B':
            std::cout << std::stoi(match[2]) << " " << std::stoi(match[3]) << std::endl;
            break;
        case 'D':
            std::cout << std::stoi(match[2]) << " " << std::stoi(match[3]) << std::endl;
            break;
        default:
            break;
        }
    }
}

float Level::getSpeedRead()
{
    return this->_speedRead;
}

float Level::getDelayRead()
{
    return this->_delayRead;
}

void Level::setDelayRead(float delayRead)
{
    this->_delayRead = delayRead;
}