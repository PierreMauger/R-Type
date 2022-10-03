#include "ECS/System/Render/RenderSystem.hpp"

using namespace ECS;

RenderSystem::RenderSystem()
{
    this->_window = new sf::RenderWindow(sf::VideoMode(800, 600), "R-Type");
    this->_window->setFramerateLimit(60);
    this->_gui.setWindow(this->_window);
}

void RenderSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    Component &modelId = componentManager.getComponent(typeid(ModelID));

    if (this->_window->isOpen()) {
        while (this->_window->pollEvent(this->_event)) {
            ImGui::SFML::ProcessEvent(this->_event);
            if (this->_event.type == sf::Event::Closed)
                this->_window->close();
        }
        this->_window->clear();
        ImGui::SFML::Update(*this->_window, this->_clock.restart());
        this->_gui.drawGUI(componentManager, entityManager);
        this->_gui.drawEntityGUI(componentManager, entityManager);
        ImGui::SFML::Render(*this->_window);
        this->_window->display();
    }
}
