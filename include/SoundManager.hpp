#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP

#include <SFML/Audio.hpp>
#include <map>
#include <string>

class SoundManager {
public:
    void loadSound(const std::string& name, const std::string& filename);
    void playSound(const std::string& name);

private:
    std::map<std::string, sf::SoundBuffer> soundBuffers;
    std::map<std::string, sf::Sound> sounds;
};

#endif // SOUNDMANAGER_HPP
