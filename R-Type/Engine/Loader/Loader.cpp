#include "Loader.hpp"
#include <chrono>
#include <thread>

using namespace eng;

Loader::Loader()
{
}

std::vector<sf::Texture> &Loader::getTextures()
{
    return this->_textures;
}

std::vector<sf::Sprite> &Loader::getSprites()
{
    return this->_sprites;
}

std::vector<sf::SoundBuffer> &Loader::getSounds()
{
    return this->_sounds;
}

void Loader::loadSprites(std::vector<std::string> paths)
{
    std::set<std::filesystem::path> sorted;

    for (auto &path : paths) {
        try {
            for (auto &file_name : std::filesystem::directory_iterator(path))
                sorted.insert(file_name.path());

            for (auto &file_name : sorted) {
                sf::Texture *texture = new sf::Texture();
                sf::Sprite sprite;

                if (texture->loadFromFile(p.path().string())) {
                    sprite.setTexture(*texture);
                    this->_textures.push_back(*texture);
                    this->_sprites.push_back(sprite);
                }
            }
        } catch (std::runtime_error &error) {
            std::cerr << error.what() << std::endl;
        }
        sorted.clear();
    }
}

void Loader::loadSounds(std::vector<std::string> paths)
{
    std::set<std::filesystem::path> sorted;

    for (auto &path : paths) {
        try {
            for (auto &file_name : std::filesystem::directory_iterator(path))
                sorted.insert(file_name.path());

            for (auto &file_name : sorted) {
                sf::SoundBuffer sound;

                if (sound.loadFromFile(p.path().string())) {
                    this->_sounds.push_back(sound);
                }
            }
        } catch (std::runtime_error &error) {
            std::cerr << error.what() << std::endl;
        }
        sorted.clear();
    }
}

sf::Texture &Loader::getTexture(std::size_t index)
{
    return this->_textures[index];
}

sf::Sprite &Loader::getSprite(std::size_t index)
{
    return this->_sprites[index];
}

sf::SoundBuffer &Loader::getSound(std::size_t index)
{
    return this->_sounds[index];
}
