#include "Loader.hpp"

using namespace eng;

Loader::Loader()
{
}

std::deque<sf::Texture> &Loader::getTextures()
{
    return this->_textures;
}

std::shared_ptr<std::vector<sf::Sprite>> Loader::getSprites()
{
    return std::make_shared<std::vector<sf::Sprite>>(this->_sprites);
}

std::shared_ptr<std::vector<sf::SoundBuffer>> Loader::getSounds()
{
    return std::make_shared<std::vector<sf::SoundBuffer>>(this->_sounds);
}

void Loader::loadSprites(std::vector<std::string> paths)
{
    for (auto &path : paths) {
        try {
            for (auto &p : std::filesystem::directory_iterator(path)) {
                sf::Texture texture;
                sf::Sprite sprite;

                if (texture.loadFromFile(p.path())) {
                    sprite.setTexture(texture);
                    this->_textures.push_back(texture);
                    this->_sprites.push_back(sprite);
                }
            }
        } catch (std::runtime_error &error) {
            std::cerr << error.what() << std::endl;
        }
    }
}

void Loader::loadSounds(std::vector<std::string> paths)
{
    for (auto &path : paths) {
        try {
            for (auto &p : std::filesystem::directory_iterator(path)) {
                sf::SoundBuffer sound;

                if (sound.loadFromFile(p.path())) {
                    this->_sounds.push_back(sound);
                }
            }
        } catch (std::runtime_error &error) {
            std::cerr << error.what() << std::endl;
        }
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
