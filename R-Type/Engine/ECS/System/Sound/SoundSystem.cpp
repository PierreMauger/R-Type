#include "Engine/ECS/System/Sound/SoundSystem.hpp"

using namespace eng;

SoundSystem::SoundSystem(std::shared_ptr<sf::Clock> clock, std::shared_ptr<std::vector<sf::SoundBuffer>> soundBuffer)
{
    this->_clock = clock;
    this->_soundBuffer = soundBuffer;
}

void SoundSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    auto &masks = entityManager.getMasks();
    std::size_t soundMask = (InfoComp::SOUNDID);

    for (std::size_t i = 0; i < masks.size(); i++) {
        if (masks[i].has_value() && ((masks[i].value() & soundMask) == soundMask)) {
            SoundID &soundId = componentManager.getSingleComponent<SoundID>(i);
            if (soundId.play && this->_sounds[i].getStatus() != sf::Sound::Status::Playing) {
                componentManager.removeAllComponents(i);
                entityManager.removeMask(i);
            }
            if (!soundId.play) {
                this->_sounds[i].setBuffer(this->_soundBuffer->at(soundId.id));
                this->_sounds[i].play();
                this->_sounds[i].setLoop(soundId.loop);
                this->_sounds[i].setPitch(soundId.pitch);
                soundId.play = true;
            }
        }
    }
}