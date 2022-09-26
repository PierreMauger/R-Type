#ifndef COMPONENTMANAGER_HPP
#define COMPONENTMANAGER_HPP

#include "Component/ComponentTypes.hpp"
#include "Includes.hpp"

namespace ECS
{
    class ComponentManager
    {
        private:
            std::map<std::type_index, std::vector<std::optional<std::any>>> _componentArray;

        public:
            ComponentManager();
            ~ComponentManager() = default;

            std::map<std::type_index, std::vector<std::optional<std::any>>> &getComponentArray();
            std::vector<std::optional<std::any>> &getComponent(std::type_index type);
            void addComponent(std::type_index type, std::vector<std::optional<std::any>> component);
            void addSpecificComponent(std::type_index type, std::size_t id, std::any component);
    };
}

#endif // COMPONENTMANAGER_HPP