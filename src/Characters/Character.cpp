//
// Created by Harry Skerritt on 22/10/2025.
//

#include "Character.h"
#include "../Game.h"

Character::Character(const sf::Vector2f &position, const sf::Vector2f &size) {
    temp_shape.setSize(size);
    temp_shape.setFillColor(sf::Color(200, 180, 150));
    temp_shape.setOrigin(size / 2.f);

    view.setSize(size);
    view.setCenter(0.f, 0.f);

    view_rect = sf::FloatRect(position.x, position.y, size.x, size.y);
}

Character::~Character() = default;

// --- Functionality ---
void Character::loadCharacter(std::array<TextureProperties, 4> textures, CreatureType type) {
    character_loaded = false;

    // Load textures from array
    body_texture = textures[0].texture;
    eye_texture = textures[1].texture;
    glasses_texture = textures[2].texture;
    hat_texture = textures[3].texture;

    if (body_texture == nullptr || eye_texture == nullptr || glasses_texture == nullptr || hat_texture == nullptr) {
        return;
    }

    // Set Body
    body_sprite.setTexture(*body_texture);
    setScaleAndOrigin(&body_sprite);
    sf::Vector2f body_offset = (SPRITE_OFFSETS.at(type).body_offset) * body_sprite.getScale().x;
    sf::Vector2f body_base_pos = {0.f, 0.f};
    sf::Vector2f body_pos = body_base_pos + body_offset;
    body_sprite.setPosition(body_pos);

    // Set Eyes
    eye_sprite.setTexture(*eye_texture);
    setScaleAndOrigin(&eye_sprite);
    sf::Vector2f eye_offset = (SPRITE_OFFSETS.at(type).eyes_offset) * eye_sprite.getScale().x;
    eye_sprite.setPosition(body_pos + eye_offset);

    // Set Glasses
    glasses_sprite.setTexture(*glasses_texture);
    setScaleAndOrigin(&glasses_sprite);
    glasses_sprite.setPosition(body_pos + eye_offset);

    // Set Hat
    hat_sprite.setTexture(*hat_texture);
    setScaleAndOrigin(&hat_sprite);
    sf::Vector2f hat_offset = (SPRITE_OFFSETS.at(type).hat_offset) * hat_sprite.getScale().x;
    hat_sprite.setPosition(body_pos + hat_offset);
    hat_sprite.setColor(sf::Color::White);

    // Get a random colour for the hat if the hat is colourable
    if (textures[3].canBeColored) {
        hat_sprite.setColor(getRandomColour());
    }

    character_loaded = true;
}

void Character::draw(sf::RenderWindow &window, Game& game) {
    sf::Vector2f win_size = game.getDefaultView().getSize();
    view.setViewport({
        view_rect.left / win_size.x,
        view_rect.top / win_size.y,
        view_rect.width / win_size.x,
        view_rect.height / win_size.y
        });

    window.setView(view);

   // Background
    window.draw(temp_shape);

    if (character_loaded) {
        window.draw(body_sprite);
        window.draw(eye_sprite);
        window.draw(glasses_sprite);
        window.draw(hat_sprite);
    }

    window.setView(game.getDefaultView());
}

// --- View ---
void Character::setViewCentre(const sf::Vector2f &centre) {
    view.setCenter(centre);
}


// --- PRIVATE ---
void Character::setScaleAndOrigin(sf::Sprite* sprite) {
    // Handle Scale
    sf::Vector2f view_size = view.getSize();
    sf::FloatRect sprite_bounds = sprite->getLocalBounds();

    float scaleX = view_size.x / sprite_bounds.width;
    float scaleY = view_size.y / sprite_bounds.height;

    float uniform_scale = std::min(scaleX, scaleY);
    sprite->setScale(uniform_scale, uniform_scale);

    // Handle Origin
    sprite->setOrigin(sprite_bounds.width / 2.f, sprite_bounds.height / 2.f);
}

sf::Color Character::getRandomColour() {
    return sf::Color(
            std::rand() % 256,
            std::rand() % 256,
            std::rand() % 256
            );
}



// Debug
// Todo: Remove before building
std::string Character::creatureTypeToString(CreatureType type) {
    switch (type) {
        case(CreatureType::BEAR):
            return "Bear";
        case(CreatureType::CHICKEN):
            return "Chicken";
        case(CreatureType::FOX):
            return "Fox";
        case(CreatureType::HEDGEHOG):
            return "Hedgehog";
        case(CreatureType::REINDEER):
            return "Reindeer";
        case(CreatureType::SKUNK):
            return "Skunk";
        case(CreatureType::SQUIRREL):
            return "Squirrel";
        case(CreatureType::WOLF):
            return "Wolf";
        case(CreatureType::NONE):
            return "None";
        default:
            return "Hmm...";
    }
}