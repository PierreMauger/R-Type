#ifndef COMPONENTMANAGER_HPP
#define COMPONENTMANAGER_HPP

#include "Engine/ECS/Component/Component.hpp"
#include "Engine/ECS/Component/ComponentTypes.hpp"
#include "Includes.hpp"

namespace eng
{
    class ComponentManager
    {
        private:
            std::vector<std::pair<std::type_index, Component>> _componentArray;

        public:
            ComponentManager();
            ~ComponentManager() = default;

            void addComponent(std::type_index type, Component component);
            void initNewComponent();
            void destroyComponent(std::size_t id, std::type_index type);
            void killEntity(std::size_t id);

            std::vector<std::pair<std::type_index, Component>> &getComponentArray();
            Component &getComponent(std::type_index type);
    };
}

#endif // COMPONENTMANAGER_HPP
