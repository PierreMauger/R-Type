/**
 * @file Component.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief Functions definitions for a component in the ComponentManager.
 * @copyright Epitech Rennes 2022
*/

#ifndef COMPONENT_HPP
#define COMPONENT_HPP

/// @cond
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
     * @brief An engine's component.
     * @class Component
    */
    class Component
    {
        private:
            std::vector<std::optional<std::any>> _component;

        public:
            /**
             * @brief Component constructor.
             * @fn Component()
            */
            Component();
            /**
             * @brief Component destructor.
             * @fn ~Component()
            */
            ~Component() = default;

            /**
             * @brief Add data to a component.
             * @fn void addData(std::size_t id, std::any data)
             * @param id Id of the data to add data at.
             * @param data Data to add to the component.
            */
            void addData(std::size_t id, std::any data);
            /**
             * @brief Emplace data in a component.
             * @fn void emplaceData(std::size_t id, std::any data)
             * @param id Id of the data to emplace at.
             * @param data Data to emplace in the component.
             * @throw Throws an error if the id is out of range.
            */
            void emplaceData(std::size_t id, std::any data);
            /**
             * @brief Destroy a data field in the component.
             * @fn void destroyData(std::size_t id)
             * @param id Id of the data field to destroy in the component.
            */
            void destroyData(std::size_t id);

            /**
             * @brief Get the number of fields of data in the component.
             * @fn std::size_t getSize()
             * @return The number of fields of data in the component.
            */
            std::size_t getSize();
            /**
             * @brief Get data from a component.
             * @fn std::optional<std::any> &getField(std::size_t id)
             * @param id Id of the data to get.
             * @return The data at id in the component.
            */
            std::optional<std::any> &getField(std::size_t id);
    };
}

#endif // COMPONENT_HPP
