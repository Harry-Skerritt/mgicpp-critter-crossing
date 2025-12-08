//
// Created by Harry Skerritt on 08/12/2025.
//

#include "AudioManager.h"

#include "SFML/Audio/Music.hpp"

#include <iostream>
#include <ostream>

AudioManager &AudioManager::getInstance()
{
  static AudioManager instance;
  return instance;
}

AudioManager::AudioManager() = default;
AudioManager::~AudioManager() = default;

bool AudioManager::loadMusicClip(const std::string &music_name,
                                 const std::string &file_name,
                                 const std::string &resource_location)
{
  std::shared_ptr<sf::Music> music = std::make_shared<sf::Music>();
  std::string music_path = resource_location + file_name;

  if (music_name.empty())
  {
    std::cout << "AudioManager: music_name is empty" << std::endl;
    return false;
  }

  if (!music->openFromFile(music_path))
  {
    std::cout << "AudioManager: Failed to load music: " << music_name << std::endl;
    return false;
  }

  music_clips.insert({music_name, music});
  return true;
}

bool AudioManager::loadSoundClip(const std::string &sound_name,
                                 const std::string &file_name,
                                 const std::string &resource_location)
{
  std::string sound_path = resource_location + file_name;

  if (sound_name.empty())
  {
    std::cout << "AudioManager: sound_name is empty" << std::endl;
    return false;
  }

  sf::SoundBuffer buffer;

  if (!buffer.loadFromFile(sound_path))
  {
    std::cout << "AudioManager: Failed to load music: " << sound_name << std::endl;
    return false;
  }

  std::shared_ptr<sf::Sound> sound = std::make_shared<sf::Sound>(buffer);
  sound_clips.insert({sound_name, sound});
  return true;
}

void AudioManager::playMusicClip(const std::string &music_name)
{
  if (music_name.empty()) {
    throw std::invalid_argument("AudioManager: music_name is empty");
  }

  auto iterator = music_clips.find(music_name);
  if (iterator == music_clips.end() || !(iterator->second))
  {
    throw std::invalid_argument("AudioManager: music not found: " + music_name);
  }

  iterator->second->play();
}

void AudioManager::playSoundClip(const std::string &sound_name)
{
  if (sound_name.empty()) {
    throw std::invalid_argument("AudioManager: sound_name is empty");
  }

  auto iterator = sound_clips.find(sound_name);
  if (iterator == sound_clips.end() || !(iterator->second))
  {
    throw std::invalid_argument("AudioManager: sound not found: " + sound_name);
  }

  iterator->second->play();
}

