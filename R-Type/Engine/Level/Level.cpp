#include "Level.hpp"

using namespace eng;

void Level::initializeLevelFormat(std::vector<std::string> &lines)
{
    std::smatch match;
    this->_speedRead = (1920 / 3 / 60) + 0.5;
    this->_delayRead = 0;

    if (std::regex_match(lines[0], std::regex("^#.*"))) {
        if (std::regex_search(lines[0], match, std::regex(".*charPerScreen:([0-9]+(\\.[0-9]+)?)"))) {
            this->_charPerScreen = std::stoi(match[1]);
            this->_sizeChar = 1920 / std::stoi(match[1]);
        } else
            throw std::runtime_error("Level: charPerScreen not found in level file.");
        lines.erase(lines.begin());
    } else
        throw std::runtime_error("Level: Invalid file format.");
    for (std::size_t i = 0; i < lines.size();) {
        if (std::regex_match(lines[i], std::regex("^--.*"))) {
            lines.erase(lines.begin() + i);
            continue;
        }
        lines[i].erase(std::remove(lines[i].begin(), lines[i].end(), '-'), lines[i].end());
        i++;
    }
}

Level::Level(std::vector<std::string> lines)
{
    this->_index = 0;
    this->_charPerScreen = 1;
    this->_sizeChar = 0;

    initializeLevelFormat(lines);
    for (std::size_t i = 0, mult = 0; i < lines[0].size(); i++) {
        for (std::size_t j = 0; j < lines.size(); j++) {
            switch (lines[j][i]) {
            case 'E':
                this->_level += "E(" + std::to_string(static_cast<int>(mult * this->_sizeChar)) + ":" + std::to_string(1080 / lines.size() * j) + ")";
                break;
            case 'B':
                this->_level += "B(" + std::to_string(static_cast<int>(mult * this->_sizeChar)) + ":" + std::to_string(1080 / lines.size() * j) + ")";
                break;
            case 'D':
                this->_level += "D(" + std::to_string(static_cast<int>(mult * this->_sizeChar)) + ":" + std::to_string(1080 / lines.size() * j) + ")";
                break;
            case 'C':
                this->_level += "C(" + std::to_string(static_cast<int>(mult * this->_sizeChar)) + ":" + std::to_string(1080 / lines.size() * j) + ")";
                break;
            case 'O':
                this->_level += "O(" + std::to_string(static_cast<int>(mult * this->_sizeChar)) + ":" + std::to_string(1080 / lines.size() * j) + ")";
                break;
            default:
                this->_level += "";
                break;
            }
        }
        mult + 1 == this->_charPerScreen ? mult = 0 : mult++;
        this->_level += "|";
    }
}

void Level::parseStringLevel(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager, std::size_t &syncId, std::smatch match, std::string levelStr)
{
    if (std::regex_search(levelStr, match, std::regex("([A-Z])\\(([0-9]+):([0-9]+)\\)"))) {
        this->_index += match[0].length();
        switch (match[1].str()[0]) {
        case 'E':
            EnemyPreload::preload(graphic, entityManager, componentManager, syncId, sf::Vector2f(std::stoi(match[2]) + graphic.getScreenSize()->x, std::stoi(match[3])));
            break;
        case 'B':
            BossPreload::preload(graphic, entityManager, componentManager, syncId, sf::Vector2f(std::stoi(match[2]) + graphic.getScreenSize()->x, std::stoi(match[3])));
            break;
        case 'D':
            DevourerPreload::preload(graphic, entityManager, componentManager, syncId, sf::Vector2f(std::stoi(match[2]) + graphic.getScreenSize()->x, std::stoi(match[3])));
            break;
        case 'C':
            CthulhuPreload::preload(graphic, entityManager, componentManager, syncId, sf::Vector2f(std::stoi(match[2]) + graphic.getScreenSize()->x, std::stoi(match[3])));
            break;
        case 'O':
            ObstaclePreload::preload(graphic, entityManager, componentManager, syncId, sf::Vector2f(std::stoi(match[2]) + graphic.getScreenSize()->x, std::stoi(match[3])));
            break;
        default:
            break;
        }
    }
}

void Level::parseLevel(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager, std::size_t &syncId)
{
    float compt = 0;
    std::smatch match;

    if (this->_index >= this->_level.size()) {
        // std::cout << "Level: End of level." << std::endl;
        return;
    }
    if (this->_index == this->_level.size() - 1) {
        this->_index++;
        return;
    }
    for (std::string levelStr = (this->_level.substr(this->_index)); compt != this->_charPerScreen && !levelStr.empty(); levelStr = (this->_level.substr(this->_index))) {
        if (this->_level[this->_index] == '|') {
            this->_index++;
            compt++;
            continue;
        }
        parseStringLevel(graphic, entityManager, componentManager, syncId, match, levelStr);
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
