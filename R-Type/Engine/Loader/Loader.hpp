#ifndef LOADER_HPP
#define LOADER_HPP

#include "Includes.hpp"

namespace eng
{
    class Loader
    {
        private:
            std::vector<sf::Texture> _textures;
            std::vector<sf::Sprite> _sprites;

            std::vector<sf::SoundBuffer> _sounds;

        public:
            Loader();
            ~Loader() = default;

            std::vector<sf::Texture> &getTextures();
            std::vector<sf::Sprite> &getSprites();

            void loadSprites(std::vector<std::string> path);
            void loadSounds(std::vector<std::string> path);
    };
}

#endif // LOADER_HPP
