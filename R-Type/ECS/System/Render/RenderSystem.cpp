#include "ECS/System/Render/RenderSystem.hpp"

using namespace ECS;

RenderSystem::RenderSystem()
{
    this->_window = new sf::RenderWindow(sf::VideoMode(800, 600), "R-Type");
    this->_window->setFramerateLimit(60);
    ImGui::SFML::Init(*this->_window);
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
        this->drawGUI(componentManager, entityManager);
        ImGui::SFML::Render(*this->_window);
        this->_window->display();
    }
}

void RenderSystem::drawGUI(ComponentManager &componentManager, EntityManager &entityManager)
{
    ImGui::Begin("Entities");

    if (ImGui::BeginTable("Entities", 3)) {
        ImGui::TableSetupColumn("ID");
        ImGui::TableSetupColumn("Mask");
        ImGui::TableSetupColumn("Actions");
        ImGui::TableHeadersRow();
        auto &masks = entityManager.getMasks();
        for (std::size_t i = 0; i < masks.size(); i++) {
            if (masks[i].has_value()) {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%lu", i);
                ImGui::TableNextColumn();
                ImGui::Text("%b", masks[i].value());
                ImGui::TableNextColumn();
                if (ImGui::Button(std::string("Remove##" + std::to_string(i)).c_str())) {
                    entityManager.removeMask(i);
                }
                ImGui::SameLine();
                if (ImGui::Button(std::string("Update##" + std::to_string(i)).c_str())) {
                    entityManager.updateMask(i, masks[i].value());
                }
            } else {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%lu", i);
                ImGui::TableNextColumn();
                ImGui::Text("None");
                ImGui::TableNextColumn();
                if (ImGui::Button(std::string("Add##" + std::to_string(i)).c_str())) {
                    entityManager.addMask(i, 0);
                }
            }
        }
        ImGui::EndTable();
        if (ImGui::Button("Add Entity")) {
            entityManager.addMask(masks.size(), std::nullopt);
        }
    }
    ImGui::End();
}
