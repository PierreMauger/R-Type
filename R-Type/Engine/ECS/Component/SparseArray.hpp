#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "Engine/ECS/Component/ComponentTypes.hpp"
#include "Includes.hpp"

namespace eng
{
    class SparseArray
    {
        private:
            std::vector<std::optional<std::any>> _data;

        public:
            SparseArray();
            ~SparseArray() = default;

            void addData(std::size_t id, std::any data);
            void emplaceData(std::size_t id, std::any data);
            void destroyData(std::size_t id);

            std::size_t getSize();
            std::optional<std::any> &getField(std::size_t id);
            void clear();
    };
}

#endif // COMPONENT_HPP
