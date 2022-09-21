#include "Includes.hpp"

class Component
{
    private:
        std::map<std::type_index, std::vector<std::optional<std::any>>> _componentArray;

    public:
        Component();
        ~Component() = default;

        std::map<std::type_index, std::vector<std::optional<std::any>>> &getComponentArray();
        std::vector<std::optional<std::any>> &getComponent(std::type_index type);
        void addComponent(std::type_index type, std::vector<std::optional<std::any>> component);
};
