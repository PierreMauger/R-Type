#include "Engine/ECS/PreloadEntities/ParallaxPreload.hpp"
#include "Engine/Engine.hpp"
#include "Includes.hpp"

void mainLoop(eng::ECS &ecs, eng::Graphic &graphic)
{
    while (graphic.getWindow()->isOpen()) {
        while (graphic.getWindow()->pollEvent(*graphic.getEvent())) {
            ImGui::SFML::ProcessEvent(*graphic.getEvent());
            if (graphic.getEvent()->type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                graphic.getWindow()->close();
        }
        graphic.getWindow()->clear(sf::Color::Black);
        ecs.update();
        graphic.getWindow()->display();
    }
}

int main(void)
{
    eng::Engine engine;
    eng::SystemManager &systemManager = engine.getECS().getSystemManager();
    eng::EntityManager &entityManager = engine.getECS().getEntityManager();
    eng::ComponentManager &componentManager = engine.getECS().getComponentManager();
    eng::Graphic &graphic = engine.getGraphic();

    // setup system & component
    systemManager.addSystem(std::make_shared<eng::InputSystem>(graphic.getEvent(), graphic.getClock()));
    systemManager.addSystem(std::make_shared<eng::PhysicSystem>(graphic.getWindow()));
    systemManager.addSystem(std::make_shared<eng::RenderSystem>(graphic.getWindow(), graphic.getClock(), engine.getLoader()));
    systemManager.addSystem(std::make_shared<eng::GUISystem>(graphic.getWindow()));

    componentManager.addComponent(typeid(Position), {});
    componentManager.addComponent(typeid(Velocity), {});
    componentManager.addComponent(typeid(SpriteID), {});
    componentManager.addComponent(typeid(Controllable), {});
    componentManager.addComponent(typeid(Parallax), {});
    componentManager.addComponent(typeid(Speed), {});
    componentManager.addComponent(typeid(CooldownShoot), {});
    componentManager.addComponent(typeid(Parent), {});

    // create background
    eng::ParallaxPreload parallaxPreload;

    parallaxPreload.preload(entityManager, componentManager);

    // create spaceship
    std::size_t id = entityManager.addMask(
        (eng::InfoEntity::POS | eng::InfoEntity::VEL | eng::InfoEntity::SPRITEID | eng::InfoEntity::SPEED | eng::InfoEntity::CONTROLLABLE | eng::InfoEntity::COOLDOWNSHOOT),
        componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{1});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{10, 0, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{0, 0, 0});
    componentManager.getComponent(typeid(Speed)).emplaceData(id, Speed{2});
    componentManager.getComponent(typeid(Controllable)).emplaceData(id, Controllable{true});
    componentManager.getComponent(typeid(CooldownShoot)).emplaceData(id, CooldownShoot{0, 2});

    // create cooldownBar
    id = entityManager.addMask((eng::InfoEntity::POS | eng::InfoEntity::SPRITEID | eng::InfoEntity::PARENT), componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{8});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{10, (float)graphic.getWindow()->getSize().y - 20, 0});
    componentManager.getComponent(typeid(Parent)).emplaceData(id, Parent{6});

    mainLoop(engine.getECS(), graphic);
    return 0;
}
