#ifndef CHARACTERCREATOR_H
#define CHARACTERCREATOR_H

#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <map>
#include <array>

enum class CreatureType { BEAR = 0, CHICKEN, FOX, HEDGEHOG, REINDEER, SKUNK, SQUIRREL, WOLF, NONE };
enum class TextureType { BODY = 0, EYES, GLASSES, HATS, COUNT };

struct TextureEntry {
  std::shared_ptr<sf::Texture> texture;
  float weight;
  CreatureType creatureType;
  bool canBeColoured;
};


struct TextureProperties {
  std::shared_ptr<sf::Texture> texture;
  sf::Color* texture_colour;
};

struct CharacterAssetData {
  std::shared_ptr<sf::Texture> body_texture;
  std::shared_ptr<sf::Texture> eye_texture;
  std::shared_ptr<sf::Texture> glasses_texture;
  std::shared_ptr<sf::Texture> hat_texture;
  sf::Color* hat_colour;
  CreatureType creature_type;
};



class CharacterCreator
{
// Funcs
public:
  CharacterCreator();
  ~CharacterCreator();

  bool LoadCharacterTextures();
  CharacterAssetData ChooseCharacter();
  CreatureType getCreatureType();


private:
  bool AddTexture(TextureType type, std::string fileLoc, float probability, bool canBeColoured = false, CreatureType creature = CreatureType::NONE);
  TextureProperties GetRandomTexture(TextureType type);

  // Helpers for counts
  int GetTextureCount(TextureType type);
  void GetTotalTextureCount();
  static sf::Color* getRandomColour();


// Vars
public:
private:
  const std::string RESOURCES_LOC = "../Data/Images/Characters/";

  std::map<TextureType, std::vector<TextureEntry>> textures;
  std::map<TextureType, int> texture_count;
  CreatureType last_creature_type = CreatureType::NONE;




};


#endif //CHARACTERCREATOR_H
