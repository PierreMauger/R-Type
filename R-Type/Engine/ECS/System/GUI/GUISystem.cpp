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
            } else if (ImGui::Button(std::string("Create##" + std::to_string(i)).c_str())) {
                entityManager.addMask(0, componentManager);
            }
        }
        ImGui::EndTable();
        const float footerReserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
        ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footerReserve), false, ImGuiWindowFlags_HorizontalScrollbar);
        ImGui::EndChild();
        ImGui::Separator();
        if (ImGui::Button("Add New Entity"))
            entityManager.addMask(std::nullopt, componentManager);
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
                        componentManager.addComponent<Size>(this->_selectedEntity);
                        break;
                    case 3:
                        componentManager.addComponent<SpriteID>(this->_selectedEntity);
                        break;
                    case 4:
                        componentManager.addComponent<Controllable>(this->_selectedEntity);
                        break;
                    case 5:
                        componentManager.addComponent<Parallax>(this->_selectedEntity);
                        break;
                    case 6:
                        componentManager.addComponent<Projectile>(this->_selectedEntity);
                        break;
                    case 7:
                        componentManager.addComponent<Life>(this->_selectedEntity);
                        break;
                    case 8:
                        componentManager.addComponent<Enemy>(this->_selectedEntity);
                        break;
                    case 9:
                        componentManager.addComponent<Appearance>(this->_selectedEntity);
                        break;
                    case 10:
                        componentManager.addComponent<Disappearance>(this->_selectedEntity);
                        break;
                    case 11:
                        componentManager.addComponent<CooldownShoot>(this->_selectedEntity);
                        break;
                    case 12:
                        componentManager.addComponent<CooldownBar>(this->_selectedEntity);
                        break;
                    case 13:
                        componentManager.addComponent<LifeBar>(this->_selectedEntity);
                        break;
                    case 14:
                        componentManager.addComponent<Parent>(this->_selectedEntity);
                        break;
                    case 15:
                        componentManager.addComponent<Patern>(this->_selectedEntity);
                        break;
                    case 16:
                        componentManager.addComponent<SyncID>(this->_selectedEntity);
                        break;
                    case 17:
                        componentManager.addComponent<DropBonus>(this->_selectedEntity);
                        break;
                    case 18:
                        componentManager.addComponent<Text>(this->_selectedEntity);
                        break;
                    case 19:
                        componentManager.addComponent<SoundID>(this->_selectedEntity);
                        break;
                    case 20:
                        componentManager.addComponent<SpriteAttribut>(this->_selectedEntity);
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
        Position &position = componentManager.getSingleComponent<Position>(this->_selectedEntity);
        ImGui::DragFloat("X##pos", &position.x, 1.0f, -FLT_MAX, +FLT_MAX);
        ImGui::DragFloat("Y##pos", &position.y, 1.0f, -FLT_MAX, +FLT_MAX);
        ImGui::DragFloat("Z##pos", &position.z, 1.0f, -FLT_MAX, +FLT_MAX);
        break;
    }
    case 1: {
        Velocity &velocity = componentManager.getSingleComponent<Velocity>(this->_selectedEntity);
        ImGui::SliderFloat("X##vel", &velocity.x, -10.0f, 10.0f);
        ImGui::SliderFloat("Y##vel", &velocity.y, -10.0f, 10.0f);
        ImGui::SliderFloat("Z##vel", &velocity.z, -10.0f, 10.0f);
        break;
    }
    case 2: {
        Size &size = componentManager.getSingleComponent<Size>(this->_selectedEntity);
        ImGui::DragFloat("X##size", &size.x, 1.0f, -FLT_MAX, +FLT_MAX);
        ImGui::DragFloat("Y##size", &size.y, 1.0f, -FLT_MAX, +FLT_MAX);
        break;
    }
    case 3: {
        SpriteID &spriteID = componentManager.getSingleComponent<SpriteID>(this->_selectedEntity);
        const ImU64 increment = 1;
        ImGui::InputScalar("SpriteID", ImGuiDataType_U64, &spriteID.id, &increment);
        break;
    }
    case 4: {
        Controllable &controllable = componentManager.getSingleComponent<Controllable>(this->_selectedEntity);
        ImGui::Checkbox("Controllable", &controllable.con);
        break;
    }
    case 5: {
        Parallax &parallax = componentManager.getSingleComponent<Parallax>(this->_selectedEntity);
        ImGui::Checkbox("Parallax", &parallax.par);
        break;
    }
    case 6: {
        Projectile &projectile = componentManager.getSingleComponent<Projectile>(this->_selectedEntity);
        ImGui::Checkbox("Projectile", &projectile.proj);
        break;
    }
    case 7: {
        Life &life = componentManager.getSingleComponent<Life>(this->_selectedEntity);
        const ImU64 increment = 1;
        ImGui::InputScalar("Life", ImGuiDataType_U64, &life.life, &increment);
        break;
    }
    case 8: {
        Enemy &enemy = componentManager.getSingleComponent<Enemy>(this->_selectedEntity);
        ImGui::Checkbox("Enemy", &enemy.enemy);
        break;
    }
    case 9: {
        Appearance &app = componentManager.getSingleComponent<Appearance>(this->_selectedEntity);
        ImGui::Checkbox("Appearance", &app.app);
        ImGui::SliderFloat("Appearance time", &app.end, 0.0f, 10.0f);
        break;
    }
    case 10: {
        break;
    }
    case 11: {
        CooldownShoot &cdShoot = componentManager.getSingleComponent<CooldownShoot>(this->_selectedEntity);
        ImGui::SliderFloat("Last shoot", &cdShoot.lastShoot, 0.0f, 10.0f);
        ImGui::SliderFloat("Shoot delay", &cdShoot.shootDelay, 0.0f, 10.0f);
        ImGui::SliderFloat("Size", &cdShoot.size, 0.0f, 10.0f);
        break;
    }
    case 12: {
        CooldownBar &cdBar = componentManager.getSingleComponent<CooldownBar>(this->_selectedEntity);
        ImGui::Checkbox("CooldownBar", &cdBar.bar);
        break;
    }
    case 13: {
        LifeBar &lifeBar = componentManager.getSingleComponent<LifeBar>(this->_selectedEntity);
        ImGui::Checkbox("LifeBar", &lifeBar.bar);
        const ImU64 increment = 1;
        ImGui::InputScalar("Life Max", ImGuiDataType_U64, &lifeBar.lifeMax, &increment);
        break;
    }
    case 14: {
        Parent &parent = componentManager.getSingleComponent<Parent>(this->_selectedEntity);
        const ImU64 increment = 1;
        ImGui::InputScalar("Model ID", ImGuiDataType_U64, &parent.id, &increment);
        break;
    }
    case 15:
        break;
    case 16:
        break;
    case 17:
        break;
    case 18:
        break;
    case 19:
        break;
    case 20:
        break;
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
