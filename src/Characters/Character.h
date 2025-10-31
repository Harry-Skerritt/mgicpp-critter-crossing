//
// Created by Harry Skerritt on 22/10/2025.
//

#ifndef CHARACTER_H
#define CHARACTER_H

#pragma once
#include <SFML/Graphics.hpp>

#include "CharacterCreator/CharacterCreator.h"

#include <array>
#include <iostream>



class Game;
class Passport;

struct CharacterOffset {
    sf::Vector2f eyes_offset;
    sf::Vector2f hat_offset;
    sf::Vector2f body_offset = {0.f, 152.f};
};

class Character {
// Funcs
public:
    Character(const sf::Vector2f& position, const sf::Vector2f& size);
    ~Character();

    void loadCharacter(const CharacterAssetData& asset_data);
    void draw(sf::RenderWindow& window, Game& game);
    void drawInPassport(sf::RenderTarget& target);

    void setViewCentre(const sf::Vector2f& centre);

private:
    // Debug
    // Todo: Remove before building
    std::string creatureTypeToString(CreatureType type);

// Vars
public:

private:
    // View
    sf::View view;
    sf::FloatRect view_rect;
    sf::Vector2f view_pos;
    sf::Vector2f view_size;

    sf::RectangleShape temp_shape;

    // Vars for loading character
    bool character_loaded = false;

    // Character Textures
    std::shared_ptr<sf::Texture> body_texture = nullptr;
    std::shared_ptr<sf::Texture>  eye_texture = nullptr;
    std::shared_ptr<sf::Texture>  glasses_texture = nullptr;
    std::shared_ptr<sf::Texture>  hat_texture = nullptr;

    // Character Sprites
    sf::Sprite body_sprite;
    sf::Sprite eye_sprite;
    sf::Sprite glasses_sprite;
    sf::Sprite hat_sprite;

    const std::map<CreatureType, CharacterOffset> SPRITE_OFFSETS = {
        {CreatureType::BEAR, CharacterOffset({0, -140}, {0, -200})},
        {CreatureType::WOLF, CharacterOffset({-92, -69}, {-92, -214})},
        {CreatureType::SQUIRREL, CharacterOffset({-298, 59}, {-298, -81})},
        {CreatureType::SKUNK, CharacterOffset({-184, 0}, {-184, -168})},
        {CreatureType::CHICKEN, CharacterOffset({-19, -210}, {-19, -290})},
        {CreatureType::FOX, CharacterOffset({-145, -34}, {-145, -264})},
        {CreatureType::HEDGEHOG, CharacterOffset({0, -92}, {0, -28})},
        {CreatureType::REINDEER, CharacterOffset({-90, 134}, {-90, -11})}
    };
};



#endif //CHARACTER_H
