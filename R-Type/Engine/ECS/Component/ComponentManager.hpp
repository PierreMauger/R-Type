/**
 * @file ComponentManager.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief Functions definitions for the ComponentManager containing/handling the engine's components.
 * @copyright Epitech Rennes 2022
*/

#ifndef COMPONENTMANAGER_HPP
#define COMPONENTMANAGER_HPP

/// @cond
#include "Engine/ECS/Component/Component.hpp"
#include "Engine/ECS/Component/ComponentTypes.hpp"
#include "Includes.hpp"
/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
*/
namespace eng
{
    /**
     * @brief The engine's ComponentManager.
     * @class ComponentManager
    */
    class ComponentManager
    {
        private:
            std::map<std::type_index, Component> _componentArray;
            std::map<std::size_t, std::type_index> _orderedMap;

        public:
            /**
             * @brief ComponentManager constructor.
             * @fn ComponentManager()
            */
            ComponentManager();
            /**
             * @brief ComponentManager destructor.
             * @fn ~ComponentManager()
            */
            ~ComponentManager() = default;

            /**
             * @brief Get the components array.
             * @fn std::map<std::type_index, Component> &getComponentArray()
             * @return The components array.
            */
            std::map<std::type_index, Component> &getComponentArray();

            /**
             * @brief Get a component from the component array.
             * @fn Component &getComponent(std::type_index type)
             * @param type type of the component to get.
             * @throw Throws an error if the type is not found.
             * @return The component.
            */
            Component &getComponent(std::type_index type);
            /**
             * @brief Get a component from the component array.
             * @fn Component &getComponent(std::size_t index)
             * @param index Id of the component to get.
             * @throw Throws an error if the id is out of range.
             * @return The component.
            */
            Component &getComponent(std::size_t index);

            /**
             * @brief Get a component's type from the component array.
             * @fn std::type_index getComponentType(std::size_t index)
             * @param index Id of the component to get.
             * @throw Throws an error if the id is out of range.
             * @return The component's type.
            */
            std::type_index getComponentType(std::size_t index);
            /**
             * @brief Init a new component.
             * @fn void initNewComponent(std::size_t id)
             * @param id Id of the component to add.
            */
            void initNewComponent(std::size_t id);

            /**
             * @brief Bind a component.
             * @fn template <typename T> void bindComponent()
             * @param T Type of the component to bind.
            */
            template <typename T> void bindComponent()
            {
                this->_componentArray[std::type_index(typeid(T))] = Component();
                this->_orderedMap.try_emplace(this->_orderedMap.size(), std::type_index(typeid(T)));
            }

            /**
             * @brief Add a component.
             * @fn template <typename T> void addComponent(std::size_t id)
             * @param T Type of the component to add.
             * @param id Id of the component to add.
            */
            template <typename T> void addComponent(std::size_t id)
            {
                this->_componentArray[std::type_index(typeid(T))].addData(id, T());
            }

            /**
             * @brief Get a simple component.
             * @fn template <typename T> T &getSingleComponent(std::size_t id)
             * @param T Type of the component to get.
             * @param id Id of the component to get.
             * @return The component.
            */
            template <typename T> T &getSingleComponent(std::size_t id)
            {
                return std::any_cast<T &>(this->_componentArray[typeid(T)].getField(id).value());
            }

            /**
             * @brief Add an entity.
             * @fn void addEntity(std::size_t id)
             * @param id Id of the entity to add.
            */
            void addEntity(std::size_t id);
            /**
             * @brief Remove a single component.
             * @fn void removeSingleComponent(std::size_t id, std::type_index type)
             * @param id Id of the component to remove.
             * @param type Type of the component to remove.
             * @throw Throws an error if the type is not found.
            */
            void removeSingleComponent(std::size_t id, std::type_index type);
            /**
             * @brief Remove all components.
             * @fn void removeAllComponents(std::size_t id)
             * @param id Id of the components to remove.
            */
            void removeAllComponents(std::size_t id);
            /**
             * @brief Update a component.
             * @fn void updateComponent(std::size_t id)
             * @param id Id of the components to update.
            */
            void updateComponent(std::size_t id);
    };
}

#endif // COMPONENTMANAGER_HPP
