//
// Created by Harry Skerritt on 28/11/2025.
//

#ifndef PASSPORTSTAMP_H
#define PASSPORTSTAMP_H

#pragma once

#include <SFML/Graphics.hpp>

#include "../../Manager/FontManager/FontManager.h"
#include "../Passport.h"

class Game;

class PassportStamp {

// Funcs
public:
  PassportStamp(Game* game_ref);
  ~PassportStamp() = default;

  void init();

  void handleMouseHover(sf::Vector2f mouse_pos);
  void onMouseClick();

  void draw(sf::RenderWindow& window);

  void showStampUI(bool visible, sf::Vector2f mouse_pos, sf::Vector2f window_size);
  bool getVisible() const { return is_visible; }

  void setPassport(Passport* passport);

private:
  bool setupTextures();
  void setupText();
  void setPositions();
  void setupActiveAreas();


// Vars
public:
private:
  Game* game;

  // Buttons
  sf::Texture plank_texture_1;
  sf::Texture plank_texture_2;

  sf::Sprite approve_button_sprite;
  sf::Sprite deny_button_sprite;

  sf::Text approve_text;
  sf::Text deny_text;
  const int TEXT_SIZE = 200;

  bool approve_hovered, deny_hovered = false;

  // Button Active Areas
  sf::RectangleShape approve_active_area;
  sf::RectangleShape deny_active_area;

  sf::Vector2f active_area_size = { 1325, 355 };
  sf::Vector2f approve_area_unscaled_pos = { 26, 48 };
  sf::Vector2f deny_area_unscaled_pos = { 26, 445 };

  // Background
  sf::Texture button_background_texture;
  sf::Sprite button_background_sprite;

  // Colours
  sf::Color default_button_colour = sf::Color::White;
  sf::Color deny_hover_colour = sf::Color::Red; // Todo: Make fit better
  sf::Color approve_hover_colour = sf::Color::Green; // Todo: Make fit better

  // State
  bool is_visible = false;

  // Positions
  sf::Vector2f button_box_position;
  sf::Vector2f approve_button_unscaled_position = { 25, -423 };
  sf::Vector2f deny_button_unscaled_position = { 25, -22 };
  sf::Vector2f approve_text_unscaled_position = { 231, 67 };
  sf::Vector2f deny_text_unscaled_position = { 398, 479 };

  const float BORDER_MARGIN = 40;

  Passport* passport = nullptr;


};



#endif //PASSPORTSTAMP_H
