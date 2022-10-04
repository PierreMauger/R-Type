#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "Engine/ECS/Component/ComponentTypes.hpp"
#include "Includes.hpp"

namespace eng
{
    class Component
    {
        private:
            std::vector<std::optional<std::any>> _component;

        public:
            Component();
            ~Component() = default;

            void addEmptyField();
            void emplaceData(std::size_t id, std::any data);
            void destroyData(std::size_t id);

            std::size_t getSize();
            std::optional<std::any> &getField(std::size_t id);
    };
}

#endif // COMPONENT_HPP
