#include "ASystem.hpp"
#include "Includes.hpp"

namespace ECS
{
    class SystemManager
    {
        private:
            std::vector<std::unique_ptr<ASystem>> _systems;

        public:
            SystemManager();
            ~SystemManager();

            std::vector<std::unique_ptr<ASystem>> &getSystems();
            void addSystem(std::unique_ptr<ASystem> system);
            void updateSystems(ComponentManager componentManager);
    };
}
