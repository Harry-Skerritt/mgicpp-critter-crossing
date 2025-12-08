//
// Created by Harry Skerritt on 08/12/2025.
//

#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <string>
#include <map>

#include <SFML/Audio.hpp>

class AudioManager {

// Funcs
public:
  static AudioManager& getInstance();

  AudioManager(const AudioManager&) = delete;
  AudioManager& operator=(const AudioManager&) = delete;
  AudioManager(AudioManager&&) = delete;
  AudioManager& operator=(AudioManager&&) = delete;

  bool loadSoundClip(const std::string& sound_name, const std::string& file_name, const std::string& resource_location = "../Data/Audio/SFX/");
  bool loadMusicClip(const std::string& music_name, const std::string& file_name, const std::string& resource_location = "../Data/Audio/Music/");

  void playSoundClip(const std::string& sound_name);
  void playMusicClip(const std::string& music_name);

private:
  AudioManager();
  ~AudioManager();

  // Vars
public:
private:
  std::map<std::string, std::shared_ptr<sf::Sound>> sound_clips;
  std::map<std::string, std::shared_ptr<sf::Music>> music_clips;

};



#endif //AUDIOMANAGER_H
