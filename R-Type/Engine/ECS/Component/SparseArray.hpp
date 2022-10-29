/**
 * @file SparseArray.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief Functions definitions for a sparse array in the ComponentManager.
 * @copyright Epitech Rennes 2022
 */

#ifndef SPARSEARRAY_HPP
#define SPARSEARRAY_HPP

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
     * @brief An engine's SparseArray.
     * @class SparseArray
     */
    class SparseArray
    {
        private:
            std::vector<std::optional<std::any>> _data;

        public:
            /**
             * @brief SparseArray constructor.
             * @fn SparseArray()
             */
            SparseArray();
            /**
             * @brief SparseArray destructor.
             * @fn ~SparseArray()
             */
            ~SparseArray() = default;

            /**
             * @brief Add data to a sparse array.
             * @fn void addData(std::size_t id, std::any data)
             * @param id Id of the data to add data at.
             * @param data Data to add to the sparse array.
             */
            void addData(std::size_t id, std::any data);
            /**
             * @brief Emplace data in a sparse array.
             * @fn void emplaceData(std::size_t id, std::any data)
             * @param id Id of the data to emplace at.
             * @param data Data to emplace in the sparse array.
             * @throw Throws an error if the id is out of range.
             */
            void emplaceData(std::size_t id, std::any data);
            /**
             * @brief Destroy a data field in the sparse array.
             * @fn void destroyData(std::size_t id)
             * @param id Id of the data field to destroy in the sparse array.
             */
            void destroyData(std::size_t id);

            /**
             * @brief Get the number of fields of data in the sparse array.
             * @fn std::size_t getSize()
             * @return The number of fields of data in the sparse array.
             */
            std::size_t getSize();
            /**
             * @brief Get data from a sparse array.
             * @fn std::optional<std::any> &getField(std::size_t id)
             * @param id Id of the data to get.
             * @return The data at id in the sparse array.
             */
            std::optional<std::any> &getField(std::size_t id);
    };
}

#endif // sparse array_HPP
