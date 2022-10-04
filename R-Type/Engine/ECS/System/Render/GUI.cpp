#include "Engine/ECS/System/Render/GUI.hpp"

using namespace eng;

GUI::GUI(std::shared_ptr<sf::RenderWindow> window)
{
    ImGui::SFML::Init(*window);
}

void GUI::drawGUI(ComponentManager &componentManager, EntityManager &entityManager)
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

void GUI::drawEntityGUI(ComponentManager &componentManager, EntityManager &entityManager)
{
    auto it = componentManager.getComponentArray().begin();
    auto &masks = entityManager.getMasks();
    std::size_t id = this->_entityID;

    if (!this->_showEntityGUI)
        return;
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
                ImGui::Text("%s", it->first.name() + std::strlen(it->first.name()) / 10 + 1);
                ImGui::TableNextColumn();
                if (std::bitset<sizeof(std::size_t)>(masks[id].value()).test(i))
                    this->drawComponentGUI(it->second, it->first, id);
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

void GUI::drawComponentGUI(Component &component, std::type_index type, std::size_t id)
{
    auto &componentT = component.getField(id);

    if (componentT.has_value()) {
        if (type == typeid(Position)) {
            ImGui::DragFloat("x##1", &std::any_cast<Position &>(componentT.value()).x, 1.0f, -FLT_MAX, +FLT_MAX);
            ImGui::DragFloat("y##1", &std::any_cast<Position &>(componentT.value()).y, 1.0f, -FLT_MAX, +FLT_MAX);
            ImGui::DragFloat("z##1", &std::any_cast<Position &>(componentT.value()).z, 1.0f, -FLT_MAX, +FLT_MAX);
        } else if (type == typeid(Velocity)) {
            ImGui::DragFloat("x##2", &std::any_cast<Velocity &>(componentT.value()).x, 0.1f, -FLT_MAX, +FLT_MAX);
            ImGui::DragFloat("y##2", &std::any_cast<Velocity &>(componentT.value()).y, 0.1f, -FLT_MAX, +FLT_MAX);
            ImGui::DragFloat("z##2", &std::any_cast<Velocity &>(componentT.value()).z, 0.1f, -FLT_MAX, +FLT_MAX);
        } else if (type == typeid(ModelID)) {
            ImGui::InputScalar("", ImGuiDataType_U64, &std::any_cast<ModelID &>(componentT.value()).id);
        } else if (type == typeid(Controllable)) {
            ImGui::Checkbox("", &std::any_cast<Controllable &>(componentT.value()).con);
        } else if (type == typeid(Speed)) {
            ImGui::DragFloat("coef", &std::any_cast<Speed &>(componentT.value()).speed, 0.1f, -FLT_MAX, +FLT_MAX);
        } else if (type == typeid(CooldownShoot)) {
            ImGui::Text("Clock: %f", std::any_cast<CooldownShoot &>(componentT.value()).time);
        }
    }
}
