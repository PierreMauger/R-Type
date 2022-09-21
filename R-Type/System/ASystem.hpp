#include "Includes.hpp"
#include "Component.hpp"

class ASystem
{
    public:
        virtual ~ASystem() = default;
        virtual void update(Component component) = 0;
};
