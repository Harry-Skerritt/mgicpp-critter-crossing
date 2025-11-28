
#ifndef CRITTERCROSSING_GAME_H
#define CRITTERCROSSING_GAME_H

#pragma once
#include <SFML/Graphics.hpp>

#include "Characters/Character.h"
#include "Characters/CharacterCreator/CharacterCreator.h"
#include "Passport/Passport.h"
#include "Passport/PassportStamp/PassportStamp.h"

enum class GameState { MENU, PLAY };

class Game
{
 // Funcs
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void mouseReleased(sf::Event event);
  void keyPressed(sf::Event event);

  const sf::View& getDefaultView();

private:
    bool loadBackground();
    bool loadFonts();
    bool loadData();
    bool loadSprites();

    void dragPassport(Passport* passport);

// Vars
public:

private:
  // Debug
  bool draw_mouse_coords = false;

  sf::RenderWindow& window;
  sf::View game_view;

  GameState game_state = GameState::PLAY; // Todo: Change to Menu and add menu

  // Background
  sf::Texture background_texture;
  sf::Sprite background_sprite;

  // Desk
  sf::Texture desk_texture;
  sf::Sprite desk_sprite;
  sf::Vector2f desk_unscaled_size = { 470, 1613 };

  // Passport Slot
  sf::Texture passport_slot_texture;
  sf::Sprite passport_slot_sprite;
  sf::Vector2f passport_slot_unscaled_size = { 2198, 89 };

  // Stamp Buttons
  std::shared_ptr<PassportStamp> passport_stamp;
  bool passport_stamp_visible = false;

  // Characters
  CharacterCreator character_creator;
  std::shared_ptr<CharacterAssetData> character_data = nullptr;
  const float CHARACTER_WIDTH = 300.f;
  const float CHARACTER_HEIGHT_MULTIPLIER = 1.09f;
  std::unique_ptr<Character> temp_character;

  // Passport
  PassportDataManager passport_data_manager;
  const float PASSPORT_WIDTH = 600.f;
  const float PASSPORT_HEIGHT_MULTIPLIER = 1.391f;
  std::unique_ptr<Passport> temp_passport;

  // Passport Dragging
  Passport* passport_drag = nullptr;
  const float DRAG_OFFSET = 40;




};

#endif // CRITTERCROSSING_GAME_H
