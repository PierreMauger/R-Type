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
             * @brief Preloads the devourer of gods.
             * @fn void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager, std::size_t &syncId, sf::Vector2f pos)
             * @param graphic A reference to the engine graphics.
             * @param entityManager A reference to the EntityManager.
             * @param componentManager A reference to the ComponentManager.
             * @param syncId A reference to the synchronized id.
             * @param pos The obstacle position.
             */
            static void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager, std::shared_ptr<std::size_t> syncId, sf::Vector2f pos);

            /**
             * @brief Preloads the devourer of gods.
             * @fn void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager, std::size_t &syncId, sf::Vector2f pos)
             * @param graphic A reference to the engine graphics.
             * @param entityManager A reference to the EntityManager.
             * @param componentManager A reference to the ComponentManager.
             * @param idHead A reference to the head id.
             */
            static void preloadBody(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager, std::size_t idHead);
    };
}

#endif // DEVOUREROFGODSPRELOAD_HPP
