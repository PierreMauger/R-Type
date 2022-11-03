/**
 * @file SoundSystem.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The Sound system
 * @copyright Epitech Rennes 2022
 */

#ifndef SOUNDSYSTEM_HPP
#define SOUNDSYSTEM_HPP

/// @cond
#include "Engine/ECS/System/ISystem.hpp"
#include "Engine/Graphic/Graphic.hpp"
#include "Engine/Loader/Loader.hpp"
/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief The Sound system
     * @class SoundSystem
     */
    class SoundSystem : public virtual ISystem
    {
        private:
            std::shared_ptr<sf::Clock> _clock;
            std::shared_ptr<std::vector<sf::SoundBuffer>> _soundBuffer;
            std::map<std::size_t, sf::Sound> _sounds;

        public:
            /**
             * @brief SoundSystem constructor
             * @fn SoundSystem(Graphic &graphic, EntityManager &entityManager, std::shared_ptr<std::vector<sf::SoundBuffer>> soundBuffer)
             * @param graphic A reference to the Graphic
             * @param entityManager A reference to the EntityManager
             */
            SoundSystem(Graphic &graphic, EntityManager &entityManager, std::shared_ptr<std::vector<sf::SoundBuffer>> soundBuffer);
            /**
             * @brief SoundSystem destructor
             * @fn ~SoundSystem()
             */
            ~SoundSystem() = default;
            /**
             * @brief Update the SoundSystem
             * @fn void update(ComponentManager &componentManager, EntityManager &entityManager)
             * @param componentManager A reference to the ComponentManager
             * @param entityManager A reference to the EntityManager
             */
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // SOUNDSYSTEM_HPP
