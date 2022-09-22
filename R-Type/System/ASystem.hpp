#include "Includes.hpp"
#include "ComponentManager.hpp"

using namespace ECS;

class ASystem
{
    public:
        virtual ~ASystem() = default;
        virtual void update(ComponentManager componentManager) = 0;
};
