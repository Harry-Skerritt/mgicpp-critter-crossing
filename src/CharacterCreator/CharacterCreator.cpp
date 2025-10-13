#include "CharacterCreator.h"

CharacterCreator::CharacterCreator() {

}

CharacterCreator::~CharacterCreator() {

}



void CharacterCreator::LoadCharacterTextures() {

    // Add Bodies
    AddTexture(TextureType::BODY, "Bodies/BearBody.png", 1.0f);
    AddTexture(TextureType::BODY, "Bodies/ChickenBody.png", 1.0f);
    AddTexture(TextureType::BODY, "Bodies/FoxBody.png", 1.0f);
    AddTexture(TextureType::BODY, "Bodies/HedgehogBody.png", 1.0f);
    AddTexture(TextureType::BODY, "Bodies/ReindeerBody.png", 1.0f);
    AddTexture(TextureType::BODY, "Bodies/SkunkBody.png", 1.0f);
    AddTexture(TextureType::BODY, "Bodies/SquirrelBody.png", 1.0f);
    AddTexture(TextureType::BODY, "Bodies/WolfBody.png", 1.0f);

    // Eyes
    AddTexture(TextureType::EYES, "Eyes/Eyes1.png", 1.0f);
    AddTexture(TextureType::EYES, "Eyes/Eyes2.png", 1.0f);
    AddTexture(TextureType::EYES, "Eyes/Eyes3.png", 1.0f);
    AddTexture(TextureType::EYES, "Eyes/Eyes4.png", 1.0f);
    AddTexture(TextureType::EYES, "Eyes/Eyes5.png", 1.0f);
    AddTexture(TextureType::EYES, "Eyes/Eyes6.png", 1.0f);
    AddTexture(TextureType::EYES, "Eyes/Eyes7.png", 1.0f);

    // Glasses
    AddTexture(TextureType::GLASSES, "Glasses/None.png", 1.0f);
    AddTexture(TextureType::GLASSES, "Glasses/Glasses1.png", 1.0f);
    AddTexture(TextureType::GLASSES, "Glasses/Glasses2.png", 1.0f);
    AddTexture(TextureType::GLASSES, "Glasses/Glasses3.png", 1.0f);

    // Hats
    AddTexture(TextureType::HATS, "Hats/None.png", 1.0f);
    AddTexture(TextureType::HATS, "Hats/Hat1.png", 1.0f);
    AddTexture(TextureType::HATS, "Hats/Hat2.png", 1.0f);
    AddTexture(TextureType::HATS, "Hats/Hat3.png", 1.0f);
    AddTexture(TextureType::HATS, "Hats/Hat4.png", 1.0f);
    AddTexture(TextureType::HATS, "Hats/Hat5.png", 1.0f);
    AddTexture(TextureType::HATS, "Hats/Hat6.png", 1.0f);
    AddTexture(TextureType::HATS, "Hats/Hat7.png", 1.0f);
    AddTexture(TextureType::HATS, "Hats/Hat8.png", 1.0f);

}

void CharacterCreator::ChooseCharacter() {


}



bool CharacterCreator::AddTexture(TextureType type, std::string fileLoc, float probability) {

    sf::Texture temp_texture;
    if (!temp_texture.loadFromFile(RESOURCES_LOC + fileLoc)) {
        std::cout << "Error loading texture: " << fileLoc << std::endl;
        return false;
    }

    if (probability < 0.0f || probability > 1.0f) {
        std::cout << "Probability must be between 0.0 and 1.0" << std::endl;
        return false;
    }

    TextureEntry entry{temp_texture, probability};
    textures[type].push_back(entry);

    return true;
}

int CharacterCreator::GetTextureCount(TextureType type) {
    return textures[type].size();
}

void CharacterCreator::GetTotalTextureCount() {

}


