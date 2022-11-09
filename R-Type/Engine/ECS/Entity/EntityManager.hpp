/**
 * @file EntityManager.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief Functions definitions for the EntityManager containing/handling the entities' masks.
 * @copyright Epitech Rennes 2022
 */

#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

/// @cond
#include "Engine/ECS/Component/ComponentManager.hpp"
#include "Includes.hpp"

/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief The engine's EntityManager.
     * @class EntityManager
     */
    class EntityManager
    {
        private:
            std::vector<std::optional<std::size_t>> _masks;
            std::map<std::size_t, std::vector<std::size_t>> _maskCategory;

        public:
            /**
             * @brief EntityManager constructor.
             * @fn EntityManager()
             */
            EntityManager();
            /**
             * @brief EntityManager destructor.
             * @fn ~EntityManager()
             */
            ~EntityManager() = default;

            /**
             * @brief Get the masks vector.
             * @fn std::vector<std::optional<std::size_t>> &getMasks()
             * @return The masks vector.
             */
            std::vector<std::optional<std::size_t>> &getMasks();

            /**
             * @brief Add a mask category.
             * @fn void addMaskCategory(std::size_t category)
             * @param category The components in binary
             */
            void addMaskCategory(std::size_t category);
            /**
             * @brief Get the all the entities id of a certain category
             * @fn std::vector<std::size_t> &getMaskCategory(std::size_t category)
             * @param category The components in binary
             * @return std::vector<std::size_t>&
             */
            std::vector<std::size_t> &getMaskCategory(std::size_t category);

            /**
             * @brief Add a mask.
             * @fn std::size_t addMask(std::optional<std::size_t> mask, ComponentManager &componentManager)
             * @param mask The mask to add.
             * @param componentManager A reference to the componentManager.
             * @return The number of masks.
             */
            std::size_t addMask(std::optional<std::size_t> mask, ComponentManager &componentManager);
            /**
             * @brief Add a mask manually.
             * @fn void addManualMask(std::size_t id, std::optional<std::size_t> mask, ComponentManager &componentManager)
             * @param id The id of the mask to add.
             * @param mask The mask to add.
             * @param componentManager A reference to the componentManager.
             */
            void addManualMask(std::size_t id, std::optional<std::size_t> mask, ComponentManager &componentManager);
            /**
             * @brief Remove a mask.
             * @fn void removeMask(std::size_t id)
             * @param id The id of the mask to remove.
             */
            void removeMask(std::size_t id);
            /**
             * @brief Update a mask.
             * @fn void updateMask(std::size_t id, std::optional<std::size_t> mask)
             * @param id The id of the mask to update.
             */
            void updateMask(std::size_t id, std::optional<std::size_t> mask);

            /**
             * @brief Get the id by syncId
             * @fn std::size_t getBySyncId(std::size_t syncId, EntityManager &entityManager)
             * @param syncId SyncId of the entity to get.
             * @param entityManager EntityManager to get the entity from.
             * @return The id of the entity.
             */
            std::size_t getBySyncId(std::size_t syncId, ComponentManager &componentManager);

            void clear();
    };
}

#endif // ENTITYMANAGER_HPP
