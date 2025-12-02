//
// Created by Harry Skerritt on 23/10/2025.
//

#ifndef PASSPORT_H
#define PASSPORT_H

#pragma once
#include <SFML/Graphics.hpp>

#include "../../Characters/Character/Character.h"
#include "../PassportDataManager/PassportDataManager.h"

#include <fstream>
#include <string>

enum class PassportState { OPEN, CLOSED };

enum class PassportStampValue { NONE, APPROVE, REJECT };

class Passport{
// Funcs
public:
    Passport(const sf::Vector2f& position, const sf::Vector2f& size);
    ~Passport();

    void initPassport(const CharacterAssetData& data);
    void setDataManager(PassportDataManager* manager);

    void setPassportState(PassportState state) { current_state = state; }
    PassportState getPassportState() const { return current_state; }

    void setPassportStamp(PassportStampValue value);
    PassportStampValue getPassportStamp() const { return current_stamp_state; }

    void setCanBeDragged(bool value) { can_be_dragged = value; }
    bool getCanBeDragged() const { return can_be_dragged; }

    void setVisible(bool visible) { is_visible = visible; };
    bool getVisible() const { return is_visible; }

    void setPassportStamped() { passport_stamped = true; }
    void resetPassportStamped() { passport_stamped = false; }
    bool getPassportStamped() const { return passport_stamped; }

    void setZoom(float factor);
    float getZoom() const;

    void setSize(sf::Vector2f size);
    sf::Vector2f getSize() const;

    void openPassport();
    void closePassport();

    void resetPassport(sf::Vector2f& start_pos);

    // 'Sprite' funcs
    sf::FloatRect getPassportBounds() const;
    void setDragPosition(const sf::Vector2f& position);
    sf::Vector2f getPassportPosition() const;

    void draw(sf::RenderWindow &window, Game& game);

    std::string getPassportStampValue() const;



private:
    bool setupBackground();
    void setupText();
    bool setupPhoto();
    void preparePhoto();
    bool loadStamps();
    void positionStamp();


// Vars
public:
private:
    PassportDataManager* data_manager;



    // Enum States
    PassportState current_state = PassportState::CLOSED;
    PassportStampValue current_stamp_state = PassportStampValue::NONE;

    // Closed State
    sf::Texture closed_passport_texture;
    sf::Sprite closed_passport_sprite;

    // View
    sf::View view;
    sf::FloatRect view_rect;
    float zoom = 1.0f;

    // Background
    sf::Texture background_texture;
    sf::Sprite background;

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
    sf::RenderTexture photo_texture;
    sf::Sprite photo_sprite;
    sf::Vector2f character_unscaled_pos = { 162, 1552 };
    sf::Vector2f character_unscaled_size = { 691, 845 };

    // Stamp
    sf::Texture approve_stamp_texture;
    sf::Texture deny_stamp_texture;
    sf::Sprite stamp_sprite;
    bool stamps_loaded = false;
    sf::Vector2f stamp_pos_unscaled = { 513, 1300 };
    sf::Vector2f stamp_size_unscaled = { 573, 573 };
    bool passport_stamped = false;

    // Dragging
    bool can_be_dragged = true;
    bool is_visible = true;

};



#endif //PASSPORT_H
