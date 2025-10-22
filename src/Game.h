
#ifndef CRITTERCROSSING_GAME_H
#define CRITTERCROSSING_GAME_H

#include <SFML/Graphics.hpp>

#include "Characters/Character.h"
#include "Characters/CharacterCreator/CharacterCreator.h"

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

private:

// Vars
public:

private:
  sf::RenderWindow& window;

  CharacterCreator character_creator;

  std::unique_ptr<Character> temp_character;
  const float CHARACTER_WIDTH = 300.f;
  const float CHARACTER_HEIGHT_MULTIPLIER = 1.09f;



};

#endif // CRITTERCROSSING_GAME_H
