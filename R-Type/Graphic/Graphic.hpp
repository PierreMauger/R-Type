#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include "ECS/Component/ComponentManager.hpp"
#include "ECS/System/Physic/PhysicSystem.hpp"
#include "ECS/System/Render/RenderSystem.hpp"
#include "ECS/System/SystemManager.hpp"
#include "Entity/EntityManager.hpp"
#include "Includes.hpp"

namespace rdr
{
    class Graphic
    {
        private:
            std::shared_ptr<sf::RenderWindow> _window;
            sf::Event _event;

            std::vector<sf::Texture> _textures;
            std::vector<sf::Sprite> _sprites;

            std::vector<sf::SoundBuffer> _sounds;

        public:
            Graphic();
            ~Graphic() = default;

            std::shared_ptr<sf::RenderWindow> &getWindow();
            sf::Event &getEvent();

            std::vector<sf::Texture> &getTextures();
            std::vector<sf::Sprite> &getSprites();

            void loadSprites(std::vector<std::string> path);
            void loadSounds(std::vector<std::string> path);
    };
}

#endif // GRAPHIC_HPP
