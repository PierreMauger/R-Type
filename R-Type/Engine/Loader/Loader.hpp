#ifndef LOADER_HPP
#define LOADER_HPP

#include "Includes.hpp"

namespace eng
{
    class Loader
    {
        private:
            std::deque<sf::Texture> _textures;
            std::vector<sf::Sprite> _sprites;
            std::vector<sf::SoundBuffer> _sounds;

        public:
            Loader();
            ~Loader() = default;

            std::deque<sf::Texture> &getTextures();
            std::shared_ptr<std::vector<sf::Sprite>> getSprites();
            std::shared_ptr<std::vector<sf::SoundBuffer>> getSounds();

            void loadSprites(std::vector<std::string> path);
            void loadSounds(std::vector<std::string> path);

            sf::Texture &getTexture(std::size_t index);
            sf::Sprite &getSprite(std::size_t index);
            sf::SoundBuffer &getSound(std::size_t index);
    };
}

#endif // LOADER_HPP
