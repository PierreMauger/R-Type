#include "Graphic.hpp"

using namespace rdr;

Graphic::Graphic()
{
    this->_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "R-Type");
    this->_window->setFramerateLimit(60);
    this->_window->setKeyRepeatEnabled(true);
}

std::shared_ptr<sf::RenderWindow> &Graphic::getWindow()
{
    return this->_window;
}

sf::Event &Graphic::getEvent()
{
    return this->_event;
}

std::vector<sf::Texture> &Graphic::getTextures()
{
    return this->_textures;
}

std::vector<sf::Sprite> &Graphic::getSprites()
{
    return this->_sprites;
}

void Graphic::loadSprites(std::vector<std::string> paths)
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

void Graphic::loadSounds(std::vector<std::string> paths)
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
