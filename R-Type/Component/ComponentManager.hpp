#ifndef COMPONENTMANAGER_HPP
#define COMPONENTMANAGER_HPP

#include "Component/ComponentTypes.hpp"
#include "Component/Component.hpp"
#include "Includes.hpp"

namespace ECS
{
    class ComponentManager
    {
        private:
            std::map<std::type_index, Component> _componentArray;

        public:
            ComponentManager();
            ~ComponentManager() = default;

            std::map<std::type_index, Component> &getComponentArray();
            Component &getComponent(std::type_index type);
            void addComponent(std::type_index type, Component component);
    };
}

#endif // COMPONENTMANAGER_HPP
