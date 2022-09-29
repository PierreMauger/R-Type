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
            std::shared_ptr<sf::RenderWindow> window;
            sf::Event event;

        public:
            Graphic();
            ~Graphic() = default;
            std::shared_ptr<sf::RenderWindow> &getWindow();
            sf::Event &getEvent();
            bool isOpen();
            void display();
            void close();
            bool pollEvent(sf::Event &event);
            void clear(const sf::Color &color = sf::Color(0, 0, 0, 255));
    };
}

#endif // GRAPHIC_HPP