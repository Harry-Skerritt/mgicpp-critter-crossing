
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));


}

Game::~Game()
{


}

bool Game::init()
{
  temp_character = std::make_unique<Character>(sf::Vector2f(200, 200), sf::Vector2f(CHARACTER_WIDTH, (CHARACTER_WIDTH * CHARACTER_HEIGHT_MULTIPLIER)));
  character_creator.LoadCharacterTextures();

  return true;
}

void Game::update(float dt)
{

}

void Game::render()
{
  temp_character->draw(window);
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);


}

void Game::keyPressed(sf::Event event)
{

  if (event.type == sf::Event::KeyPressed) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
      temp_character->loadCharacter(character_creator.ChooseCharacter(), character_creator.getCreatureType());
    }
  }

}


