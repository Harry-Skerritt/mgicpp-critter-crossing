//
// Created by Harry Skerritt on 22/10/2025.
//

#include "Character.h"
#include "../Game.h"
#include "../Helpers/ScaleTools/ScaleTools.h"

Character::Character(const sf::Vector2f &position, const sf::Vector2f &size)
{
    temp_shape.setSize(size);
    temp_shape.setFillColor(sf::Color(200, 180, 150, 0));
    temp_shape.setOrigin(size / 2.f);


    view.setSize(size);
    view.setCenter(0.f, 0.f);

    view_rect = sf::FloatRect(position.x, position.y, size.x, size.y);
    view_pos = position;
    view_size = size;
}

Character::~Character() = default;

// --- Functionality ---
void Character::loadCharacter(const CharacterAssetData& asset_data)
{
    if (&asset_data == nullptr) {
        return;
    }

    character_loaded = false;
    CreatureType type = asset_data.creature_type;

    // Load textures from array
    body_texture = asset_data.body_texture;
    eye_texture = asset_data.eye_texture;
    glasses_texture = asset_data.glasses_texture;
    hat_texture = asset_data.hat_texture;

    if (body_texture == nullptr || eye_texture == nullptr || glasses_texture == nullptr || hat_texture == nullptr)
    {
        return;
    }

    // Set Body
    body_sprite.setTexture(*body_texture);
    ScaleTools::scaleToView(body_sprite, view, true);
    sf::Vector2f body_offset = (SPRITE_OFFSETS.at(type).body_offset) * body_sprite.getScale().x;
    sf::Vector2f body_base_pos = {0.f, 0.f};
    sf::Vector2f body_pos = body_base_pos + body_offset;
    body_sprite.setPosition(body_pos);

    // Set Eyes
    eye_sprite.setTexture(*eye_texture);
    ScaleTools::scaleToView(eye_sprite, view, true);
    sf::Vector2f eye_offset = (SPRITE_OFFSETS.at(type).eyes_offset) * eye_sprite.getScale().x;
    eye_sprite.setPosition(body_pos + eye_offset);

    // Set Glasses
    glasses_sprite.setTexture(*glasses_texture);
    ScaleTools::scaleToView(glasses_sprite, view, true);
    glasses_sprite.setPosition(body_pos + eye_offset);

    // Set Hat
    hat_sprite.setTexture(*hat_texture);
    ScaleTools::scaleToView(hat_sprite, view, true);
    sf::Vector2f hat_offset = (SPRITE_OFFSETS.at(type).hat_offset) * hat_sprite.getScale().x;
    hat_sprite.setPosition(body_pos + hat_offset);
    hat_sprite.setColor(sf::Color::White);

    // Get a random colour for the hat if the hat is colourable
    if (asset_data.hat_colour != nullptr)
    {
        hat_sprite.setColor(*asset_data.hat_colour);
    } else
    {
        hat_sprite.setColor(sf::Color::White);
    }

    character_loaded = true;
}



void Character::draw(sf::RenderWindow &window, Game& game)
{
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

    if (character_loaded)
    {
        window.draw(body_sprite);
        window.draw(eye_sprite);
        window.draw(glasses_sprite);
        window.draw(hat_sprite);
    }

    window.setView(game.getDefaultView());
}

void Character::drawInPassport(sf::RenderTarget& target)
{

    target.setView(view);

    target.draw(temp_shape);

    if (character_loaded)
    {
        target.draw(body_sprite);
        target.draw(eye_sprite);
        target.draw(glasses_sprite);
        target.draw(hat_sprite);
    }

}



// --- View ---
void Character::setViewCentre(const sf::Vector2f &centre)
{
    view.setCenter(centre);
}


// Debug
// Todo: Remove before building
std::string Character::creatureTypeToString(CreatureType type)
{
    switch (type)
    {
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