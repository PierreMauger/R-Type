#ifndef SCORESYSTEM_HPP
#define SCORESYSTEM_HPP

#include "Engine/ECS/ECS.hpp"
#include "Engine/ECS/System/ISystem.hpp"

namespace eng
{
    class ScoreSystem : public virtual ISystem
    {
        private:
            std::shared_ptr<sf::RenderWindow> _window;
            std::shared_ptr<std::vector<sf::Sprite>> _sprites;
            bool _firstTime;
            std::size_t _death;
            std::size_t _score;
            std::size_t _lastSaveScore;
            std::vector<sf::Text> _text;
            sf::Font _font;
            bool findVessel(ComponentManager &componentManager, EntityManager &entityManager, Controllable &Controllable);
            void createVessel(ComponentManager &componentManager, EntityManager &entityManager, std::shared_ptr<std::vector<sf::Sprite>> sprites,
                              std::shared_ptr<sf::RenderWindow> window);
            void createText(ComponentManager &componentManager, EntityManager &entityManager);

        public:
            ScoreSystem(std::shared_ptr<sf::RenderWindow> _window, std::shared_ptr<std::vector<sf::Sprite>> _sprites);
            ~ScoreSystem() = default;
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // SCORESYSTEM_HPP