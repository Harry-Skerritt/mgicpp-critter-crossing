
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

  characterCreator.LoadCharacterTextures();

  characterCreator.ChooseCharacter();

  return true;
}

void Game::update(float dt)
{
  body.setTexture(characterCreator.body_texture);
  body.setScale(0.25f, 0.25f);
  body.setPosition(0, 0);

  eyes.setTexture(characterCreator.eyes_texture);
  eyes.setScale(0.25f, 0.25f);
  eyes.setPosition(0, 0);

  glasses.setTexture(characterCreator.glasses_texture);
  glasses.setScale(0.25f, 0.25f);
  glasses.setPosition(0, 0);

  hat.setTexture(characterCreator.hat_texture);
  hat.setScale(0.25f, 0.25f);
  hat.setPosition(0, 0);

}

void Game::render()
{
  window.draw(body);
  window.draw(eyes);
  window.draw(glasses);
  window.draw(hat);

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
      characterCreator.ChooseCharacter();
    }
  }

}


