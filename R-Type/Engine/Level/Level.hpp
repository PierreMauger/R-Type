#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "Engine/ECS/PreloadEntities/BossPreload.hpp"
#include "Engine/ECS/PreloadEntities/CthulhuPreload.hpp"
#include "Engine/ECS/PreloadEntities/DevourerOfGodsPreload.hpp"
#include "Engine/ECS/PreloadEntities/EnemyPreload.hpp"
#include "Includes.hpp"

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng

{
    /**
     * @brief The Engine's level.
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
            void parseLevel(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager);
            float getSpeedRead();
            float getDelayRead();
            void setDelayRead(float delayRead);
    };
}

#endif // LEVEL_HPP