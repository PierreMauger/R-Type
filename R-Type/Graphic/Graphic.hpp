#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include "ECS/Component/ComponentManager.hpp"
#include "ECS/System/Physic/PhysicSystem.hpp"
#include "ECS/System/Render/RenderSystem.hpp"
#include "ECS/System/SystemManager.hpp"
#include "Entity/EntityManager.hpp"

namespace rdr
{
    class Graphic
    {
        private:
            std::shared_ptr<sf::RenderWindow> _window;
            std::shared_ptr<sf::Event> _event;

        public:
            Graphic();
            ~Graphic() = default;
            std::shared_ptr<sf::RenderWindow> getWindow();
            std::shared_ptr<sf::Event> getEvent();
    };
}

#endif // GRAPHIC_HPP