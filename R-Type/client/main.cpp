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
    std::size_t id = 0;

    // graphic.loadSprites({"R-Type/assets/Sprites"});
    // graphic.loadSounds({"R-Type/assets/Sprites"});

    // setup system & component
    engine.getECS().getSystemManager().addSystem(std::make_shared<eng::InputSystem>(engine.getGraphic().getEvent(), engine.getGraphic().getClock()));
    engine.getECS().getSystemManager().addSystem(std::make_shared<eng::PhysicSystem>(engine.getGraphic().getWindow()));
    engine.getECS().getSystemManager().addSystem(std::make_shared<eng::RenderSystem>(engine.getGraphic().getWindow(), engine.getGraphic().getClock(), engine.getLoader()));
    engine.getECS().getSystemManager().addSystem(std::make_shared<eng::GUISystem>(engine.getGraphic().getWindow()));

    engine.getECS().getComponentManager().addComponent(typeid(Position), {});
    engine.getECS().getComponentManager().addComponent(typeid(Velocity), {});
    engine.getECS().getComponentManager().addComponent(typeid(SpriteID), {});
    engine.getECS().getComponentManager().addComponent(typeid(Controllable), {});
    engine.getECS().getComponentManager().addComponent(typeid(Parallax), {});
    engine.getECS().getComponentManager().addComponent(typeid(Speed), {});
    engine.getECS().getComponentManager().addComponent(typeid(CooldownShoot), {});
    engine.getECS().getComponentManager().addComponent(typeid(Parent), {});

    // create background
    id = engine.getECS().getEntityManager().addMask((eng::InfoEntity::SPRITEID | eng::InfoEntity::POS | eng::InfoEntity::VEL | eng::InfoEntity::PARALLAX),
                                                    engine.getECS().getComponentManager());
    engine.getECS().getComponentManager().initNewComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{3});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(id, Position{0, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(id, Velocity{-0.2, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
    id = engine.getECS().getEntityManager().addMask((eng::InfoEntity::SPRITEID | eng::InfoEntity::POS | eng::InfoEntity::VEL | eng::InfoEntity::PARALLAX),
                                                    engine.getECS().getComponentManager());
    engine.getECS().getComponentManager().initNewComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{3});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(id, Position{800, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(id, Velocity{-0.2, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
    id = engine.getECS().getEntityManager().addMask((eng::InfoEntity::SPRITEID | eng::InfoEntity::POS | eng::InfoEntity::VEL | eng::InfoEntity::PARALLAX),
                                                    engine.getECS().getComponentManager());
    engine.getECS().getComponentManager().initNewComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{4});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(id, Position{0, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(id, Velocity{-0.6, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
    id = engine.getECS().getEntityManager().addMask((eng::InfoEntity::SPRITEID | eng::InfoEntity::POS | eng::InfoEntity::VEL | eng::InfoEntity::PARALLAX),
                                                    engine.getECS().getComponentManager());
    engine.getECS().getComponentManager().initNewComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{5});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(id, Position{0, 100, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(id, Velocity{-1, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
    id = engine.getECS().getEntityManager().addMask((eng::InfoEntity::SPRITEID | eng::InfoEntity::POS | eng::InfoEntity::VEL | eng::InfoEntity::PARALLAX),
                                                    engine.getECS().getComponentManager());
    engine.getECS().getComponentManager().initNewComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{6});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(id, Position{400, 250, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(id, Velocity{-1.5, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
    id = engine.getECS().getEntityManager().addMask((eng::InfoEntity::SPRITEID | eng::InfoEntity::POS | eng::InfoEntity::VEL | eng::InfoEntity::PARALLAX),
                                                    engine.getECS().getComponentManager());
    engine.getECS().getComponentManager().initNewComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{7});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(id, Position{800, 100, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(id, Velocity{-2, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});

    // create spaceship
    id = engine.getECS().getEntityManager().addMask(
        (eng::InfoEntity::POS | eng::InfoEntity::VEL | eng::InfoEntity::SPRITEID | eng::InfoEntity::SPEED | eng::InfoEntity::CONTROLLABLE | eng::InfoEntity::COOLDOWNSHOOT),
        engine.getECS().getComponentManager());
    engine.getECS().getComponentManager().initNewComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{1});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(id, Position{10, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(id, Velocity{0, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Speed)).emplaceData(id, Speed{2});
    engine.getECS().getComponentManager().getComponent(typeid(Controllable)).emplaceData(id, Controllable{true});
    engine.getECS().getComponentManager().getComponent(typeid(CooldownShoot)).emplaceData(id, CooldownShoot{0, 2});

    // create cooldownBar
    id = engine.getECS().getEntityManager().addMask((eng::InfoEntity::POS | eng::InfoEntity::SPRITEID | eng::InfoEntity::PARENT), engine.getECS().getComponentManager());
    engine.getECS().getComponentManager().initNewComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{8});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(id, Position{10, (float)engine.getGraphic().getWindow()->getSize().y - 20, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parent)).emplaceData(id, Parent{6});

    mainLoop(engine.getECS(), engine.getGraphic());
    return 0;
}
