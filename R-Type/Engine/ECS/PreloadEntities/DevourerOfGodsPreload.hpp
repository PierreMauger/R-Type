/**
 * @file DevourerOfGodsPreload.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief Preload the Devourer Of Gods (terraria boss).
 * @copyright Epitech Rennes 2022
*/

#ifndef DEVOUREROFGODSPRELOAD_HPP
#define DEVOUREROFGODSPRELOAD_HPP

/// @cond
#include "Engine/ECS/PreloadEntities/EntityPreload.hpp"
/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
*/
namespace eng
{
    /**
     * @brief Preloads the Devourer Of Gods.
     * @class DevourerOfGodsPreload
    */
    class DevourerPreload : public EntityPreload
    {
        public:
            /**
             * @brief Preloads the Devourer Of Gods.
             * @fn void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager) override
             * @param engine A reference to the engine.
            */
            void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager) override;
    };
}

#endif // DEVOUREROFGODSPRELOAD_HPP