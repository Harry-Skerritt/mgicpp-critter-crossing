#ifndef CHARACTERCREATOR_H
#define CHARACTERCREATOR_H

#include <iostream>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

enum class CreatureType { BEAR = 0, CHICKEN, FOX, HEDGEHOG, REINDEER, SKUNK, SQUIRREL, WOLF };
enum class TextureType { BODY, EYES, GLASSES, HATS };

struct TextureEntry {
  sf::Texture texture;
  float probability;
};

class CharacterCreator
{
  public:
    CharacterCreator();
    ~CharacterCreator();

    void LoadCharacterTextures();
    void ChooseCharacter();



  private:
    const std::string RESOURCES_LOC = "../Data/Images/Characters/";

    std::map<TextureType, std::vector<TextureEntry>> textures;
    std::map<TextureType, int> texture_count;
    CreatureType lastCreatureType;


    bool AddTexture(TextureType type, std::string fileLoc, float probability);
    int GetTextureCount(TextureType type);
    void GetTotalTextureCount();



};


#endif //CHARACTERCREATOR_H
