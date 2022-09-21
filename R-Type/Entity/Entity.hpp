#include "Includes.hpp"

class Entity
{
    private:
        std::vector<std::optional<size_t>> _masks;

    public:
        Entity();
        ~Entity() = default;

        std::vector<std::optional<size_t>> &getMasks();
        void addMask(size_t id, std::optional<size_t> mask);
        void removeMask(size_t id);
        void updateMask(size_t id, std::optional<size_t> mask);
};
