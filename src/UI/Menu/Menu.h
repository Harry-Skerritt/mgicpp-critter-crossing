//
// Created by Harry Skerritt on 02/12/2025.
//

#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

class Game;

class Menu {
// Funcs
public:
  Menu(Game* game_ref);
  ~Menu() = default;

  void init();
  void update(float dt);
  void draw(sf::RenderWindow& window);

  void handleMouse(sf::Vector2f mouse_pos);
  void handleMouseClick();

private:

  void loadSprites();
  void loadButtons();
  void setPositions();

// Vars
public:
private:

  Game* game;

  // Background
  sf::Texture menu_background_texture;
  sf::Sprite menu_background;

  // Menu
  sf::Texture title_texture;
  sf::Sprite title;

  // Hedgehog Guy
  sf::Texture hedgehog_texture;
  sf::Sprite hedgehog;

  // Play Button
  sf::Texture play_background_texture;
  sf::Sprite play_background;
  sf::Text play_text;
  sf::RectangleShape play_active_area;
  bool play_active = false;

  // Quit Button
  sf::Texture quit_background_texture;
  sf::Sprite quit_background;
  sf::Text quit_text;
  sf::RectangleShape quit_active_area;
  bool quit_active = false;

  sf::Color regular_button_colour = sf::Color::White;
  sf::Color hovered_button_colour = sf::Color(252, 194, 4, 255);
};



#endif //MENU_H
