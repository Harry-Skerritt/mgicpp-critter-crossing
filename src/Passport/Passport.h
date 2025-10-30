//
// Created by Harry Skerritt on 23/10/2025.
//

#ifndef PASSPORT_H
#define PASSPORT_H

#pragma once
#include <SFML/Graphics.hpp>

#include "../Characters/Character.h"
#include "PassportDataManager/PassportDataManager.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>



class Passport {
// Funcs
public:
    Passport(const sf::Vector2f& position, const sf::Vector2f& size);
    ~Passport();

    void initPassport(const CharacterAssetData& data);
    void setDataManager(PassportDataManager* dataManager);

    void draw(sf::RenderWindow &window, Game& game);

    const sf::View& getDefaultView();

    const sf::FloatRect& getViewRect() { return view_rect; }

private:
    bool setupBackground();
    bool setupText();


// Vars
public:
private:
    PassportDataManager* data_manager;

    // View
    sf::View view;
    sf::FloatRect view_rect;

    // Background
    sf::Texture background_texture;
    sf::Sprite background;

    sf::RectangleShape background_rect;

    // Data
    Character* display_character;
    std::string display_name;
    std::string display_age;
    std::string display_district;

    // Text
    int unscaled_font_size = 90;
    sf::Text name_text; // Pos: 959, 1552
    sf::Vector2f name_text_pos_unscaled = {959, 1552};

    sf::Text age_text; // Pos: 959, 1763
    sf::Vector2f age_text_pos_unscaled = {959, 1763};

    sf::Text district_text; // Pos: 959, 1964
    sf::Vector2f district_text_pos_unscaled = {959, 1964};

    sf::Color text_colour = sf::Color(255, 235, 205);

    // Character
    std::shared_ptr<CharacterAssetData> asset_data = nullptr;
    std::unique_ptr<Character> passport_character;
    sf::Vector2f character_unscaled_pos = { 162, 1152 };
    sf::Vector2f character_unscaled_size = { 691, 845 };



};



#endif //PASSPORT_H
