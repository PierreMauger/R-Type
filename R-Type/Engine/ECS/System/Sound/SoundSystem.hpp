#ifndef SOUNDSYSTEM_HPP
#define SOUNDSYSTEM_HPP

#include "Engine/ECS/System/ISystem.hpp"
#include "Engine/Loader/Loader.hpp"

namespace eng
{
    class SoundSystem : public virtual ISystem
    {
        private:
            std::shared_ptr<sf::Clock> _clock;
            std::shared_ptr<std::vector<sf::SoundBuffer>> _soundBuffer;
            std::map<std::size_t, sf::Sound> _sounds;

        public:
            SoundSystem(std::shared_ptr<sf::Clock> clock, std::shared_ptr<std::vector<sf::SoundBuffer>> soundBuffer);
            ~SoundSystem() = default;
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // SOUNDSYSTEM_HPP