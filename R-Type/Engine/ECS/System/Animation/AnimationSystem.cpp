#include "Engine/ECS/System/Animation/AnimationSystem.hpp"

using namespace eng;

AnimationSystem::AnimationSystem(std::shared_ptr<sf::Event> event, std::shared_ptr<sf::Clock> clock)
{
    this->_event = event;
    this->_clock = clock;
}

void AnimationSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
}