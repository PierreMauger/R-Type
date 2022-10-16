/**
 * @file ScoreSystem.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The score system
 * @copyright Epitech Rennes 2022
 */

#ifndef SCORESYSTEM_HPP
#define SCORESYSTEM_HPP

/// @cond
#include "Engine/ECS/ECS.hpp"
#include "Engine/ECS/System/ISystem.hpp"
/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief The score system
     * @class ScoreSystem
     */
    class ScoreSystem : public virtual ISystem
    {
        private:
            std::shared_ptr<sf::RenderWindow> _window;
            std::shared_ptr<std::vector<sf::Sprite>> _sprites;
            bool _firstTime;
            std::size_t _death;
            std::size_t _lastSaveScore;
            std::vector<sf::Text> _text;
            sf::Font _font;
            bool findVessel(ComponentManager &componentManager, EntityManager &entityManager, Controllable &Controllable);
            void createVessel(ComponentManager &componentManager, EntityManager &entityManager, std::shared_ptr<std::vector<sf::Sprite>> sprites,
                              std::shared_ptr<sf::RenderWindow> window);
            void createText(ComponentManager &componentManager, EntityManager &entityManager);

        public:
            /**
             * @brief ScoreSystem constructor
             * @fn ScoreSystem(std::shared_ptr<sf::RenderWindow> _window, std::shared_ptr<std::vector<sf::Sprite>> _sprites)
             * @param _window A shared pointer to the window
             * @param _sprites A shared pointer to vector of sprites
             */
            ScoreSystem(std::shared_ptr<sf::RenderWindow> _window, std::shared_ptr<std::vector<sf::Sprite>> _sprites);
            /**
             * @brief ScoreSystem destructor
             * @fn ~ScoreSystem()
             */
            ~ScoreSystem() = default;
            /**
             * @brief Update the ScoreSystem
             * @fn void update(ComponentManager &componentManager, EntityManager &entityManager)
             * @param componentManager A reference to the ComponentManager
             * @param entityManager A reference to the EntityManager
             */
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // SCORESYSTEM_HPP
