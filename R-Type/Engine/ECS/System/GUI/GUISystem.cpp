#include "Engine/ECS/System/GUI/GUISystem.hpp"

using namespace eng;

GUISystem::GUISystem(std::shared_ptr<sf::RenderWindow> window)
{
    this->_window = window;
    if (!ImGui::SFML::Init(*this->_window))
        std::cout << "ImGui counldn't init" << std::endl;
}

GUISystem::~GUISystem()
{
    ImGui::SFML::Shutdown();
}

void GUISystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    ImGui::SFML::Update(*this->_window, this->_clock.restart());
    if (this->_showEntityManager)
        this->drawEntityManager(componentManager, entityManager);
    if (this->_showEntityDetails)
        this->drawEntityDetails(componentManager, entityManager);
    ImGui::SFML::Render(*this->_window);
}

void GUISystem::drawEntityManager(ComponentManager &componentManager, EntityManager &entityManager)
{
    std::size_t size = componentManager.getComponentArray().size();
    ImGui::Begin("Entities", &this->_showEntityManager);

    if (ImGui::BeginTable("Entities", 3, ImGuiTableFlags_Resizable)) {
        ImGui::TableSetupColumn("ID");
        ImGui::TableSetupColumn("Mask");
        ImGui::TableSetupColumn("Actions");
        ImGui::TableHeadersRow();
        auto &masks = entityManager.getMasks();
        for (std::size_t i = 0; i < masks.size(); i++) {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("%lu", i);
            ImGui::TableNextColumn();
            masks[i].has_value() ? ImGui::Text("%s", this->formatBool(masks[i].value(), size).c_str()) : ImGui::Text("None");
            ImGui::TableNextColumn();
            if (masks[i].has_value()) {
                if (ImGui::Button(std::string("Remove##" + std::to_string(i)).c_str())) {
                    entityManager.removeMask(i);
                    componentManager.removeAllComponents(i);
                    this->_showEntityDetails = false;
                }
                ImGui::SameLine();
                if (ImGui::Button(std::string("Modify##" + std::to_string(i)).c_str())) {
                    this->_showEntityDetails = true;
                    this->_selectedEntity = i;
                }
            } else {
                if (ImGui::Button(std::string("Create##" + std::to_string(i)).c_str()))
                    entityManager.addMask(i, 0);
            }
        }
        ImGui::EndTable();
        const float footerReserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
        ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footerReserve), false, ImGuiWindowFlags_HorizontalScrollbar);
        ImGui::EndChild();
        ImGui::Separator();
        if (ImGui::Button("Add New Entity"))
            entityManager.addMask(masks.size(), std::nullopt);
    }
    ImGui::End();
}

void GUISystem::drawEntityDetails(ComponentManager &componentManager, EntityManager &entityManager)
{
    ImGui::Begin("Entity Details", &this->_showEntityDetails);
    auto &masks = entityManager.getMasks();

    ImGui::Text("ID: %lu", this->_selectedEntity);
    for (std::size_t i = 0; i < componentManager.getComponentArray().size(); i++) {
        if (masks[this->_selectedEntity].value() & (1 << i)) {
            if (ImGui::CollapsingHeader(FORMAT_NAME(componentManager.getComponentType(i).name()), ImGuiTreeNodeFlags_DefaultOpen)) {
                this->drawEntityComponent(componentManager, i);
                if (ImGui::Button(std::string("Remove##" + std::to_string(i)).c_str())) {
                    entityManager.updateMask(this->_selectedEntity, masks[this->_selectedEntity].value() & ~(1 << i));
                    componentManager.removeSingleComponent(this->_selectedEntity, componentManager.getComponentType(i));
                }
            }
            ImGui::Separator();
        }
    }
    const float footerReserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
    ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footerReserve), false, ImGuiWindowFlags_HorizontalScrollbar);
    ImGui::EndChild();
    ImGui::Separator();
    if (ImGui::CollapsingHeader("Add Component")) {
        for (std::size_t i = 0; i < componentManager.getComponentArray().size(); i++) {
            if (!(masks[this->_selectedEntity].value() & (1 << i))) {
                if (ImGui::Selectable(FORMAT_NAME(componentManager.getComponentType(i).name()))) {
                    entityManager.updateMask(this->_selectedEntity, masks[this->_selectedEntity].value() | (1 << i));
                    switch (i) {
                    case 0:
                        componentManager.addComponent<Position>(this->_selectedEntity);
                        break;
                    case 1:
                        componentManager.addComponent<Velocity>(this->_selectedEntity);
                        break;
                    case 2:
                        componentManager.addComponent<SpriteID>(this->_selectedEntity);
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }
    ImGui::End();
}

void GUISystem::drawEntityComponent(ComponentManager &componentManager, std::size_t type)
{
    switch (type) {
    case 0: {
        Position &position = std::any_cast<Position &>(componentManager.getComponent(type).getField(this->_selectedEntity).value());
        ImGui::DragFloat("X##pos", &position.x, 1.0f, -FLT_MAX, +FLT_MAX);
        ImGui::SameLine();
        ImGui::DragFloat("Y##pos", &position.y, 1.0f, -FLT_MAX, +FLT_MAX);
        ImGui::SameLine();
        ImGui::DragFloat("Z##pos", &position.z, 1.0f, -FLT_MAX, +FLT_MAX);
        break;
    }
    case 1: {
        Velocity &velocity = std::any_cast<Velocity &>(componentManager.getComponent(type).getField(this->_selectedEntity).value());
        ImGui::SliderFloat("X##vel", &velocity.x, -10, 10);
        ImGui::SliderFloat("Y##vel", &velocity.y, -10, 10);
        ImGui::SliderFloat("Z##vel", &velocity.z, -10, 10);
        break;
    }
    case 2: {
        SpriteID &spriteID = std::any_cast<SpriteID &>(componentManager.getComponent(type).getField(this->_selectedEntity).value());
        const ImU64 increment = 1;
        ImGui::InputScalar("Model ID", ImGuiDataType_U64, &spriteID, &increment);
        break;
    }
    default:
        break;
    }
}

std::string GUISystem::formatBool(std::size_t value, std::size_t size)
{
    std::string binary = std::bitset<64>(value).to_string();
    std::string result = "";

    for (std::size_t i = 64 - size; i < 64; i++) {
        result += binary[i];
        if (i % 8 == 7)
            result += " ";
    }
    return result;
}
