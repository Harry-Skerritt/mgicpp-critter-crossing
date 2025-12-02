
#ifndef CRITTERCROSSING_GAME_H
#define CRITTERCROSSING_GAME_H

#pragma once
#include <SFML/Graphics.hpp>

#include "Characters/Character.h"
#include "Characters/CharacterCreator/CharacterCreator.h"
#include "Effects/FeedbackFade.h"
#include "Passport/Passport.h"
#include "Passport/PassportArea/PassportArea.h"
#include "Passport/PassportStamp/PassportStamp.h"
#include "UI/ProgressCounter.h"

enum class GameState { MENU, PLAY };

class Game
{
 // Funcs
 public:
  Game(sf::RenderWindow& window);
  ~Game() = default;
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void mouseReleased(sf::Event event);
  void keyPressed(sf::Event event);

  const sf::View& getDefaultView();

  void setGameState(GameState state) { game_state = state; }

  bool getDebug() const { return debug_mode; };

private:
    bool loadBackground();
    static bool loadFonts();
    bool loadData();
    bool loadSprites();
    void setupSlots();

    void dragPassport(Passport* passport);

    void handleDragAreas(Passport* passport);
    sf::Vector2f getDragPosition();
    void handlePassportDropped();
    void validatePassport(Passport* passport);


    void makePassportSmall();
    void makePassportBig();

    void createNewRound();

    bool decideIfMatch() const;



// Vars
public:

private:
  // Debug
  bool debug_mode = false;

  // UI
  int rounds_played = 1;
  int rounds_correct = 0;
  ProgressCounter progress_counter;

  sf::RenderWindow& window;
  sf::View game_view;
  float current_zoom = 1.0f;

  GameState game_state = GameState::PLAY; // Todo: Change to Menu and add menu

  // Background
  sf::Texture background_texture;
  sf::Sprite background_sprite;

  // Desk
  sf::Texture desk_texture;
  sf::Sprite desk_sprite;
  sf::Vector2f desk_unscaled_size = { 470, 1613 };

  // Passport Slot
  PassportArea passport_area;
  sf::Vector2f passport_area_unscaled_pos = { 2198, 89 };

  PassportArea return_area;
  sf::Vector2f return_area_unscaled_pos = { 965, 1699 };

  // Stamp Buttons
  std::shared_ptr<PassportStamp> passport_stamp;
  bool passport_stamp_visible = false;

  // Characters
  CharacterCreator character_creator;
  std::shared_ptr<CharacterAssetData> character_data = nullptr;
  const float CHARACTER_WIDTH = 629.f;
  const float CHARACTER_HEIGHT_MULTIPLIER = 1.09f;
  std::unique_ptr<Character> character_object;
  sf::Vector2f character_unscaled_pos = { 800, 270 };

  // Passport
  PassportDataManager passport_data_manager;
  std::unique_ptr<Passport> passport_object;
  std::shared_ptr<CharacterAssetData> passport_character_data = nullptr;

  sf::Vector2f passport_spawn_pos_unscaled = { 1888, 1130 };
  sf::Vector2f passport_spawn_size_unscaled = { 653, 939 };
  sf::Vector2f passport_main_size_unscaled = { 1306, 1879 };
  const float PASSPORT_SCALE_FACTOR = 2.f;

  // Passport Dragging
  Passport* passport_drag = nullptr;
  const float DRAG_OFFSET = 40;

  // Feedback
  FeedbackFade feedback;
  sf::Color correct_feedback = sf::Color(95, 183, 40, 255);
  sf::Color incorrect_feedback = sf::Color(183, 57, 40, 255);


  const float MATCH_PROBABILITY = 0.2f;


};

#endif // CRITTERCROSSING_GAME_H
