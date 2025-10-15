#ifndef CHARACTERCREATOR_H
#define CHARACTERCREATOR_H

#include <iostream>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

enum class CreatureType { BEAR = 0, CHICKEN, FOX, HEDGEHOG, REINDEER, SKUNK, SQUIRREL, WOLF, NONE };
enum class TextureType { BODY = 0, EYES, GLASSES, HATS, COUNT };

struct TextureEntry {
  std::shared_ptr<sf::Texture> texture;
  float weight;
  CreatureType creatureType;
};

class CharacterCreator
{
public:
  CharacterCreator();
  ~CharacterCreator();

  void LoadCharacterTextures();
  void ChooseCharacter();

  sf::Texture body_texture;
  sf::Texture eyes_texture;
  sf::Texture glasses_texture;
  sf::Texture hat_texture;




private:
  const std::string RESOURCES_LOC = "../Data/Images/Characters/";

  std::map<TextureType, std::vector<TextureEntry>> textures;
  std::map<TextureType, int> texture_count;
  CreatureType lastCreatureType = CreatureType::NONE;




  bool AddTexture(TextureType type, std::string fileLoc, float probability, CreatureType creature = CreatureType::NONE);
  const sf::Texture* GetRandomTexture(TextureType type);

  // Helpers for counts
  int GetTextureCount(TextureType type);
  void GetTotalTextureCount();



};


#endif //CHARACTERCREATOR_H
