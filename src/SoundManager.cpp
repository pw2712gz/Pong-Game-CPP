#include "SoundManager.hpp"
#include <iostream>

void SoundManager::loadSound(const std::string& name, const std::string& filename) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filename)) {
        std::cerr << "Failed to load sound file: " << filename << std::endl;
    } else {
        soundBuffers[name] = buffer;
        sf::Sound sound;
        sound.setBuffer(soundBuffers[name]);
        sounds[name] = sound;
    }
}

void SoundManager::playSound(const std::string& name) {
    if (sounds.find(name) != sounds.end()) {
        sounds[name].play();
    } else {
        std::cerr << "Sound not found: " << name << std::endl;
    }
}
