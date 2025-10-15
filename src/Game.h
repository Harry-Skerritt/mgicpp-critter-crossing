
#ifndef CRITTERCROSSING_GAME_H
#define CRITTERCROSSING_GAME_H

#include <SFML/Graphics.hpp>

#include "CharacterCreator/CharacterCreator.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);

 private:
  sf::RenderWindow& window;
  sf::Sprite body;
  sf::Sprite eyes;
  sf::Sprite glasses;
  sf::Sprite hat;

  CharacterCreator characterCreator;



};

#endif // CRITTERCROSSING_GAME_H
