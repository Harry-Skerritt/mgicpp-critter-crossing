#include "CharacterCreator.h"

CharacterCreator::CharacterCreator() { }

CharacterCreator::~CharacterCreator() = default;

void CharacterCreator::LoadCharacterTextures() {

    // Add Bodies
    AddTexture(TextureType::BODY, "Bodies/BearBody.png", 1.0f, false, CreatureType::BEAR);
    AddTexture(TextureType::BODY, "Bodies/ChickenBody.png", 1.0f, false, CreatureType::CHICKEN);
    AddTexture(TextureType::BODY, "Bodies/FoxBody.png", 1.0f, false, CreatureType::FOX);
    AddTexture(TextureType::BODY, "Bodies/HedgehogBody.png", 1.0f, false, CreatureType::HEDGEHOG);
    AddTexture(TextureType::BODY, "Bodies/ReindeerBody.png", 1.0f, false, CreatureType::REINDEER);
    AddTexture(TextureType::BODY, "Bodies/SkunkBody.png", 1.0f, false, CreatureType::SKUNK);
    AddTexture(TextureType::BODY, "Bodies/SquirrelBody.png", 1.0f, false, CreatureType::SQUIRREL);
    AddTexture(TextureType::BODY, "Bodies/WolfBody.png", 1.0f, false,  CreatureType::WOLF);

    // Eyes
    AddTexture(TextureType::EYES, "Eyes/Eyes1.png", 1.0f);
    AddTexture(TextureType::EYES, "Eyes/Eyes2.png", 1.0f);
    AddTexture(TextureType::EYES, "Eyes/Eyes3.png", 1.0f);
    AddTexture(TextureType::EYES, "Eyes/Eyes4.png", 1.0f);
    AddTexture(TextureType::EYES, "Eyes/Eyes5.png", 1.0f);
    AddTexture(TextureType::EYES, "Eyes/Eyes6.png", 1.0f);
    AddTexture(TextureType::EYES, "Eyes/Eyes7.png", 1.0f);

    // Glasses
    AddTexture(TextureType::GLASSES, "Glasses/None.png", 0.8f);
    AddTexture(TextureType::GLASSES, "Glasses/Glasses1.png", 0.15f);
    AddTexture(TextureType::GLASSES, "Glasses/Glasses2.png", 0.1f);
    AddTexture(TextureType::GLASSES, "Glasses/Glasses3.png", 0.15f);

    // Hats
    AddTexture(TextureType::HATS, "Hats/None.png", 0.8f);
    AddTexture(TextureType::HATS, "Hats/Hat1.png", 0.15f, true);
    AddTexture(TextureType::HATS, "Hats/Hat2.png", 0.1f);
    AddTexture(TextureType::HATS, "Hats/Hat3.png", 0.15f, true);
    AddTexture(TextureType::HATS, "Hats/Hat4.png", 0.15f);
    AddTexture(TextureType::HATS, "Hats/Hat5.png", 0.15f, true);
    AddTexture(TextureType::HATS, "Hats/Hat6.png", 0.15f);
    AddTexture(TextureType::HATS, "Hats/Hat7.png", 0.15f, true);
    AddTexture(TextureType::HATS, "Hats/Hat8.png", 0.15f, true);

    // Get the texture count
    GetTotalTextureCount();

}

std::array<TextureProperties, 4> CharacterCreator::ChooseCharacter() {
    std::array<TextureProperties, 4> textures{};

    textures[0] = GetRandomTexture(TextureType::BODY);
    textures[1] = GetRandomTexture(TextureType::EYES);
    textures[2] = GetRandomTexture(TextureType::GLASSES);
    textures[3] = GetRandomTexture(TextureType::HATS);

    return textures;
}

CreatureType CharacterCreator::getCreatureType() {
    return last_creature_type;
}

// --- PRIVATE ---
bool CharacterCreator::AddTexture(TextureType type, std::string fileLoc, float weight, bool canBeColoured, CreatureType creature) {

    std::shared_ptr<sf::Texture> temp_texture = std::make_shared<sf::Texture>() ;
    if (!temp_texture->loadFromFile(RESOURCES_LOC + fileLoc)) {
        std::cout << "Error loading texture: " << fileLoc << std::endl;
        return false;
    }

    if (weight < 0.0f || weight > 1.0f) {
        std::cout << "Weight must be between 0.0 and 1.0" << std::endl;
        return false;
    }

    TextureEntry entry{temp_texture, weight, creature, canBeColoured};
    textures[type].push_back(entry);

    return true;
}

TextureProperties CharacterCreator::GetRandomTexture(TextureType type)
{
    TextureProperties properties{};
    const std::vector<TextureEntry>& entries = textures[type];
    if (entries.empty()) {
        std::cout << "No textures available" << std::endl;
        return properties;
    }

    int count = texture_count[type];

    // Get the total weight
    float total_weight = 0.0f;
    for (int i = 0; i < count; ++i) {
        total_weight += entries[i].weight;
    }

    // Check the weight isn't 0
    if (total_weight <= 0.0f) {
        std::cout << "Total weight is 0.0" << std::endl;
        return properties;
    }

    const TextureEntry* chosen = nullptr;
    int attempts = 0;

    // Ensure the same animal isn't picked twice in a row
    while (!chosen && attempts < 10) {
        float random = static_cast<float>(std::rand())/ RAND_MAX * total_weight;

        // Find the chosen texture
        float cumulative = 0.0f;
        for (int i = 0; i < count; ++i) {
            cumulative += entries[i].weight;
            if (random <= cumulative) {
                if (type == TextureType::BODY) {
                    if (entries[i].creatureType != last_creature_type || entries.size() == 1) {
                        chosen = &entries[i];
                    }
                } else {
                    chosen = &entries[i];
                }
                break;
            }
        }
        attempts++;
    }

    // Always return something
    if (!chosen)
        chosen = &entries.front();

    if (type == TextureType::BODY) {
        last_creature_type = chosen->creatureType;
    }

    properties.texture = chosen->texture;
    properties.canBeColored = chosen->canBeColoured;
    return properties;
}


// Helpers for counts
int CharacterCreator::GetTextureCount(TextureType type) {
    return textures[type].size();
}

void CharacterCreator::GetTotalTextureCount() {
    for (int i = 0; i < static_cast<int>(TextureType::COUNT); ++i) {
        TextureType type = static_cast<TextureType>(i);
        int count = GetTextureCount(type);

        texture_count[type] = count;
    }
}






