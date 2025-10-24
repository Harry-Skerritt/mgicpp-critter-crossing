
#ifndef CRITTERCROSSING_GAME_H
#define CRITTERCROSSING_GAME_H

#pragma once
#include <SFML/Graphics.hpp>

#include "Characters/Character.h"
#include "Characters/CharacterCreator/CharacterCreator.h"
#include "Passport/Passport.h"

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
  void keyPressed(sf::Event event);

  const sf::View& getDefaultView();

private:
    bool loadFonts();

// Vars
public:

private:
  sf::RenderWindow& window;
  sf::View game_view;

  sf::Texture background_texture;
  sf::Sprite background_sprite;


  CharacterCreator character_creator;
  const float CHARACTER_WIDTH = 300.f;
  const float CHARACTER_HEIGHT_MULTIPLIER = 1.09f;
  std::unique_ptr<Character> temp_character;

  PassportDataManager passport_data_manager;
  const float PASSPORT_WIDTH = 600.f;
  const float PASSPORT_HEIGHT_MULTIPLIER = 1.391f;
  std::unique_ptr<Passport> temp_passport;




};

#endif // CRITTERCROSSING_GAME_H
