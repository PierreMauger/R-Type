/**
 * @file Level.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The map loader handling functions.
 * @copyright Epitech Rennes 2022
 */

#ifndef LEVEL_HPP
#define LEVEL_HPP

/// @cond
#include "Engine/ECS/PreloadEntities/BossPreload.hpp"
#include "Engine/ECS/PreloadEntities/CthulhuPreload.hpp"
#include "Engine/ECS/PreloadEntities/DevourerOfGodsPreload.hpp"
#include "Engine/ECS/PreloadEntities/EnemyPreload.hpp"
#include "Engine/ECS/PreloadEntities/ObstaclePreload.hpp"
#include "Includes.hpp"

/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief The Engine's level manager.
     * @class Level
     */
    class Level
    {
        private:
            std::size_t _index;
            std::string _level;
            float _speedRead;
            float _delayRead;
            float _charPerScreen;
            float _sizeChar;
            void initializeLevelFormat(std::vector<std::string> &lines);
            void parseStringLevel(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager, std::size_t &syncId, std::smatch match, std::string levelStr);

        public:
            /**
             * @brief Level constructor.
             * @fn Level()
             */
            Level(std::vector<std::string> lines);
            /**
             * @brief Level destructor.
             * @fn ~Level()
             */
            ~Level() = default;
            /**
             * @brief Parse the level file
             * @fn void parseLevel(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager, std::size_t &syncId)
             * @param graphic A shared pointer to the engine graphics
             * @param entityManager A shared pointer to the EntityManager
             * @param componentManager A shared pointer to the ComponentManager
             * @param syncId A shared pointer to the sync id when creating an enemy
             */
            bool parseLevel(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager, std::size_t &syncId);
            /**
             * @brief Get the speed of appearance of the waves in the map
             * @fn float getSpeedRead()
             * @return The speed of appearance of the waves in the map
             */
            float getSpeedRead();
            /**
             * @brief Get the last time a wave for the map appeared
             * @fn float getDelayRead()
             * @return The last time a wave for the map appeared
             */
            float getDelayRead();
            /**
             * @brief Set the last time a wave for the map appeared
             * @fn void setDelayRead(float delayRead)
             * @param delayRead The last time a wave for the map appears
             */
            void setDelayRead(float delayRead);
    };
}

#endif // LEVEL_HPP