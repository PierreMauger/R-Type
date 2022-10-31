#include "Engine/ECS/System/Sound/SoundSystem.hpp"

using namespace eng;

SoundSystem::SoundSystem(std::shared_ptr<sf::Clock> clock, std::shared_ptr<std::vector<sf::SoundBuffer>> soundBuffer)
{
    this->_clock = clock;
    this->_soundBuffer = soundBuffer;
}

void SoundSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    std::size_t soundMask = (InfoComp::SOUNDID);

    for (auto id : entityManager.getMaskCategory(soundMask)) {
        SoundID &soundId = componentManager.getSingleComponent<SoundID>(id);
        if (soundId.play && this->_sounds[id].getStatus() != sf::Sound::Status::Playing) {
            componentManager.removeAllComponents(id);
            entityManager.removeMask(id);
        }
        if (!soundId.play) {
            this->_sounds[id].setBuffer(this->_soundBuffer->at(soundId.id));
            this->_sounds[id].play();
            this->_sounds[id].setLoop(soundId.loop);
            this->_sounds[id].setPitch(soundId.pitch);
            soundId.play = true;
        }
    }
}
