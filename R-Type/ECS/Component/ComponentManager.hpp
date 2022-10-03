#ifndef COMPONENTMANAGER_HPP
#define COMPONENTMANAGER_HPP

#include "ECS/Component/Component.hpp"
#include "ECS/Component/ComponentTypes.hpp"
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

            void addComponent(std::type_index type, Component component);
            void initEmptyComponent();
            void killEntity(std::size_t id);

            std::map<std::type_index, Component> &getComponentArray();
            Component &getComponent(std::type_index type);
    };
}

#endif // COMPONENTMANAGER_HPP
