/**
 * @file Loader.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The Engine's loader (sprites, sounds...).
 * @copyright Epitech Rennes 2022
*/

#ifndef LOADER_HPP
#define LOADER_HPP

/// @cond
#include "Includes.hpp"
/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
*/
namespace eng
{
    /**
     * @brief The Engine's loader (sprites, sounds...).
     * @class Loader
    */
    class Loader
    {
        private:
            std::vector<sf::Texture> _textures;
            std::vector<sf::Sprite> _sprites;
            std::vector<sf::SoundBuffer> _sounds;

        public:
            /**
             * @brief Loader constructor.
             * @fn Loader()
            */
            Loader();
            /**
             * @brief Loader destructor.
             * @fn ~Loader()
            */
            ~Loader() = default;

            /**
             * @brief Get a reference to the vector of sprite textures.
             * @fn std::vector<sf::Texture> &getTextures()
             * @return A reference to  vector of sprite textures.
            */
            std::vector<sf::Texture> &getTextures();
            /**
             * @brief Get a reference to the vector of sprites.
             * @fn std::vector<sf::Sprite> &getSprites()
             * @return A reference to  vector of sprites.
            */
            std::vector<sf::Sprite> &getSprites();
            /**
             * @brief Get a reference to the vector of sounds.
             * @fn std::vector<sf::SoundBuffer> &getSounds()
             * @return A reference to  vector of sounds.
            */
            std::vector<sf::SoundBuffer> &getSounds();

            /**
             * @brief Load the sprites.
             * @fn void loadSprites(std::vector<std::string> path)
             * @param path The relative pathes to search the sprites (.png) in.
            */
            void loadSprites(std::vector<std::string> path);
            /**
             * @brief Load the sounds.
             * @fn void loadSounds(std::vector<std::string> path)
             * @param path The relative pathes to search the sounds (.ogg) in.texture
            */
            void loadSounds(std::vector<std::string> path);

            /**
             * @brief Get a reference to a textures' vector texture.
             * @fn sf::Texture &getTexture(std::size_t index)
             * @param index The index of the texture in the vector.
             * @return A reference to the texture.
            */
            sf::Texture &getTexture(std::size_t index);
            /**
             * @brief Get a reference to a sprites' vector sprite.
             * @fn sf::Sprite &getSprite(std::size_t index)
             * @param index The index of the sprite in the vector.
             * @return A reference to the sprite.
            */
            sf::Sprite &getSprite(std::size_t index);
            /**
             * @brief Get a reference to a sounds' vector sound.
             * @fn sf::SoundBuffer &getSound(std::size_t index)
             * @param index The index of the sound in the vector.
             * @return A reference to the sound.
            */
            sf::SoundBuffer &getSound(std::size_t index);
    };
}

#endif // LOADER_HPP
