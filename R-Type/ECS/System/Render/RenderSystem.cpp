#include "ECS/System/Render/RenderSystem.hpp"

using namespace ECS;

RenderSystem::RenderSystem(std::shared_ptr<sf::RenderWindow> window)
{
    this->id = 0;
    this->window = window;
    this->window->setFramerateLimit(60);
}

void RenderSystem::update(ComponentManager &componentManager)
{
    Component &modelId = componentManager.getComponent(typeid(ModelID));

    for (std::size_t i = 0; i < modelId.getSize(); i++) {
        if (modelId.getField(i).has_value())
            std::any_cast<ModelID &>(modelId.getField(i).value()).id = this->id;
    }
}
