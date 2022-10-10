#include "Engine/ECS/System/GUI/GUISystem.hpp"

using namespace eng;

GUISystem::GUISystem(std::shared_ptr<sf::RenderWindow> window)
{
    this->_window = window;
    if (!ImGui::SFML::Init(*this->_window))
        std::cout << "ImGui counldn't init" << std::endl;
}

void GUISystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    ImGui::SFML::Update(*this->_window, this->_clock.restart());
    this->drawEntity(componentManager, entityManager);
    if (this->_showEntityModify)
        this->drawModifyEntity(componentManager, entityManager);
    ImGui::SFML::Render(*this->_window);
}

void GUISystem::drawEntity(ComponentManager &componentManager, EntityManager &entityManager)
{
    std::size_t size = componentManager.getComponentArray().size();
    ImGui::Begin("Entities", &this->_showEntity);

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
                masks[i].has_value() ? ImGui::Text("%s", this->formatBool(masks[i].value(), size).c_str()) : ImGui::Text("None");
                ImGui::TableNextColumn();
                if (ImGui::Button(std::string("Remove##" + std::to_string(i)).c_str())) {
                    entityManager.removeMask(i);
                    componentManager.killEntity(i);
                }
                ImGui::SameLine();
                if (ImGui::Button(std::string("Modify##" + std::to_string(i)).c_str())) {
                    this->_showEntityModify = true;
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
                    entityManager.addMask(0, componentManager);
            }
        }
        ImGui::EndTable();
        if (ImGui::Button("Add Entity"))
            entityManager.addMask(std::nullopt, componentManager);
    }
    ImGui::End();
}

void GUISystem::drawModifyEntity(ComponentManager &componentManager, EntityManager &entityManager)
{
    auto it = componentManager.getComponentArray().begin();
    auto &masks = entityManager.getMasks();

    ImGui::Begin("Modify Entity", &this->_showEntityModify);
    ImGui::Text("ID: %lu", this->_entityID);
    if (ImGui::BeginTable("Entity", 3)) {
        ImGui::TableSetupColumn("Component");
        ImGui::TableSetupColumn("Value");
        ImGui::TableSetupColumn("Action");
        ImGui::TableHeadersRow();
        if (masks[this->_entityID].has_value()) {
            for (std::size_t i = 0; i < componentManager.getComponentArray().size(); i++) {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%s", it->first.name() + std::strlen(it->first.name()) / 10 + 1);
                ImGui::TableNextColumn();
                if (std::bitset<sizeof(std::size_t)>(masks[this->_entityID].value()).test(i))
                    this->drawComponent(it->second, it->first, this->_entityID);
                else
                    ImGui::Text("None");
                ImGui::TableNextColumn();
                if (std::bitset<sizeof(std::size_t)>(masks[this->_entityID].value()).test(i)) {
                    if (ImGui::Button(std::string("Remove##" + std::to_string(i)).c_str())) {
                        entityManager.updateMask(this->_entityID, masks[this->_entityID].value() & ~(1 << i));
                        componentManager.destroyComponent(this->_entityID, it->first);
                    }
                } else {
                    if (ImGui::Button(std::string("Add##" + std::to_string(i)).c_str())) {
                        entityManager.updateMask(this->_entityID, masks[this->_entityID].value() | (1 << i));
                        // componentManager.getComponent(it->first).emplaceData(this->_entityID, it->first);
                    }
                }
                it++;
            }
        }
        ImGui::EndTable();
    }
    ImGui::End();
}

void GUISystem::drawComponent(Component &component, std::type_index type, std::size_t id)
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
        } else if (type == typeid(SpriteID)) {
            ImGui::InputScalar("##3", ImGuiDataType_U64, &std::any_cast<SpriteID &>(componentT.value()).id);
        } else if (type == typeid(Controllable)) {
            ImGui::Checkbox("##4", &std::any_cast<Controllable &>(componentT.value()).con);
        } else if (type == typeid(Parallax)) {
            ImGui::Checkbox("##5", &std::any_cast<Parallax &>(componentT.value()).par);
        } else if (type == typeid(Speed)) {
            ImGui::DragFloat("coef", &std::any_cast<Speed &>(componentT.value()).speed, 0.1f, -FLT_MAX, +FLT_MAX);
        } else if (type == typeid(CooldownShoot)) {
            ImGui::Text("%f", std::any_cast<CooldownShoot &>(componentT.value()).time);
        }
    }
}

std::string GUISystem::formatBool(std::size_t value, std::size_t size)
{
    std::string binary = std::bitset<sizeof(std::size_t)>(value).to_string();
    std::string result = "";

    for (std::size_t i = 0; i < size; i++) {
        result += binary[i];
        if (i % 8 == 7)
            result += " ";
    }
    return result;
}
