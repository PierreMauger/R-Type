#ifndef PHYSICSYSTEM_HPP
#define PHYSICSYSTEM_HPP

#include "Engine/ECS/System/ISystem.hpp"

namespace eng
{
    class PhysicSystem : public virtual ISystem
    {
        private:
            std::shared_ptr<sf::RenderWindow> _window;
            std::shared_ptr<sf::Vector2f> _screenSize;
            sf::Rect<float> _rect1;
            sf::Rect<float> _rect2;
            void createBonus(std::size_t id, std::size_t drop, ComponentManager &componentManager, EntityManager &entityManager);
            bool checkAppareance(ComponentManager &componentManager, std::size_t i, Position &pos, Velocity &vel);
            bool checkDisappearance(EntityManager &entityManager, ComponentManager &componentManager, std::size_t i, Position &pos, Velocity &vel);
            bool checkColision(Position &pos, Position &pos2, Size &sz, Size &sz2);
            bool collisionBonus(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, Position &pos);
            bool collisionEnemy(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, Position &pos);
            bool collisionFireball(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, Position &pos);

        public:
            PhysicSystem(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Vector2f> screenSize);
            ~PhysicSystem() = default;
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // PHYSICSYSTEM_HPP
