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
        if (this->_showEntityGUI)
            this->drawEntityGUI(componentManager, entityManager, this->_entityID);
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
                ImGui::Text(std::string("%0" + std::to_string(componentManager.getComponentArray().size()) + "b").c_str(), masks[i].value());
                ImGui::TableNextColumn();
                if (ImGui::Button(std::string("Remove##" + std::to_string(i)).c_str()))
                    entityManager.removeMask(i);
                ImGui::SameLine();
                if (ImGui::Button(std::string("Modify##" + std::to_string(i)).c_str())) {
                    this->_showEntityGUI = true;
                    this->_entityID = i;
                }
            } else {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%lu", i);
                ImGui::TableNextColumn();
                ImGui::Text("None");
                ImGui::TableNextColumn();
                if (ImGui::Button(std::string("Add##" + std::to_string(i)).c_str()))
                    entityManager.addMask(i, 0);
            }
        }
        ImGui::EndTable();
        if (ImGui::Button("Add Entity"))
            entityManager.addMask(masks.size(), std::nullopt);
    }
    ImGui::End();
}

void RenderSystem::drawEntityGUI(ComponentManager &componentManager, EntityManager &entityManager, std::size_t id)
{
    auto it = componentManager.getComponentArray().begin();
    auto &masks = entityManager.getMasks();

    ImGui::Begin("Modify Entity", &this->_showEntityGUI);
    ImGui::Text("ID: %lu", id);
    if (ImGui::BeginTable("Entity", 3)) {
        ImGui::TableSetupColumn("Component");
        ImGui::TableSetupColumn("Value");
        ImGui::TableSetupColumn("Action");
        ImGui::TableHeadersRow();
        if (masks[id].has_value()) {
            for (unsigned short i = 0; i < 8 && i < componentManager.getComponentArray().size(); i++) {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%s", it->first.name() + 1);
                ImGui::TableNextColumn();
                if (std::bitset<sizeof(std::size_t)>(masks[id].value()).test(i))
                    ImGui::Text("Exists");
                else
                    ImGui::Text("None");
                ImGui::TableNextColumn();
                if (std::bitset<sizeof(std::size_t)>(masks[id].value()).test(i)) {
                    if (ImGui::Button(std::string("Remove##" + std::to_string(i)).c_str()))
                        entityManager.updateMask(id, masks[id].value() & ~(1 << i));
                } else {
                    if (ImGui::Button(std::string("Add##" + std::to_string(i)).c_str()))
                        entityManager.updateMask(id, masks[id].value() | (1 << i));
                }
                it++;
            }
        }
        ImGui::EndTable();
    }
    ImGui::End();
}
