#include "Engine/ECS/System/Sound/SoundSystem.hpp"

using namespace eng;

SoundSystem::SoundSystem(Graphic &graphic, EntityManager &entityManager, std::shared_ptr<std::vector<sf::SoundBuffer>> soundBuffer)
{
    this->_clock = graphic.getClock();
    this->_soundBuffer = soundBuffer;

    entityManager.addMaskCategory(this->_soundTag);
}

void SoundSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    if (_soundBuffer->size() == 0)
        return;
    for (auto id : entityManager.getMaskCategory(this->_soundTag)) {
        if (!entityManager.getMasks()[id].has_value() || (entityManager.getMasks()[id].value() & this->_soundTag) != this->_soundTag)
            continue;
        SoundID &soundId = componentManager.getSingleComponent<SoundID>(id);
        if (soundId.play && this->_sounds[id].getStatus() != sf::Sound::Status::Playing) {
            componentManager.removeAllComponents(id);
            entityManager.removeMask(id);
            continue;
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
