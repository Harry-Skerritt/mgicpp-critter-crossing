//
// Created by Harry Skerritt on 02/12/2025.
//

#include "Menu.h"

#include "../../Game.h"
#include "../../Helpers/ScaleTools/ScaleTools.h"
#include "../../Manager/FontManager/FontManager.h"

#include <iostream>

Menu::Menu(Game *game_ref) {
   game = game_ref;
}

void Menu::init() {
   loadSprites();
   loadButtons();
   setPositions();
}

void Menu::update(float dt) {

}

void Menu::draw(sf::RenderWindow& window) {
   window.draw(menu_background);
   window.draw(title);

   window.draw(hedgehog);

   // Buttons
   window.draw(play_background);
   window.draw(play_text);
   //window.draw(play_active_area);

   window.draw(quit_background);
   window.draw(quit_text);
   //window.draw(quit_active_area);
}

void Menu::handleMouse(sf::Vector2f mouse_pos) {

   if (play_active_area.getGlobalBounds().contains(mouse_pos))
   {
      play_text.setFillColor(hovered_button_colour);
      play_active = true;
   }
   else
   {
      play_text.setFillColor(regular_button_colour);
      play_active = false;
   }

   if (quit_active_area.getGlobalBounds().contains(mouse_pos))
   {
      quit_text.setFillColor(hovered_button_colour);
      quit_active = true;
   }
   else
   {
      quit_text.setFillColor(regular_button_colour);
      quit_active = false;
   }

}

void Menu::handleMouseClick() {
   if (play_active) {
      if (!game->game_reset) {
         game->resetGame();
      }

      game->setGameState(GameState::PLAY);
   }

   if (quit_active) {
      game->quitGame();
   }
}


// --- PRIVATE ---
void Menu::loadSprites() {
   // Background
   if (!menu_background_texture.loadFromFile("../Data/Images/Menu/MenuBackground.png")) {
      std::cerr << "Failed to load menu background texture" << std::endl;
   }
   menu_background.setTexture(menu_background_texture);
   menu_background.setScale(0.5f, 0.5f);

   // Title
   if (!title_texture.loadFromFile("../Data/Images/Menu/Title.png")) {
      std::cerr << "Failed to load title texture" << std::endl;
   }
   title.setTexture(title_texture);
   title.setScale(0.5f, 0.5f);

   // Play Button
   if (!play_background_texture.loadFromFile("../Data/Images/Menu/PlayButtonBackground.png")) {
      std::cerr << "Failed to load play background texture" << std::endl;
   }
   play_background.setTexture(play_background_texture);
   play_background.setScale(0.5f, 0.5f);

   // Quit Button
   if (!quit_background_texture.loadFromFile("../Data/Images/Menu/QuitButtonBackground.png")) {
      std::cerr << "Failed to load quit background texture" << std::endl;
   }
   quit_background.setTexture(quit_background_texture);
   quit_background.setScale(0.5f, 0.5f);

   // Hedgehog
   if (!hedgehog_texture.loadFromFile("../Data/Images/Menu/HedgehogGuy.png")) {
      std::cerr << "Failed to load hedgehog texture" << std::endl;
   }
   hedgehog.setTexture(hedgehog_texture);
   hedgehog.setScale(.5f, .5f);
}

void Menu::loadButtons() {
   // Play Button
   play_text.setFont(FontManager::getInstance().getFont("Passport"));
   play_text.setCharacterSize(ScaleTools::getScaledFont(350, menu_background));
   play_text.setFillColor(regular_button_colour);
   play_text.setString("PLAY");

   // Active Area - Play
   sf::Vector2f p_active_area = { (1897/2), (531/2) };
   play_active_area.setSize(p_active_area);
   sf::Vector2f p_active_pos = { 933, 858 };
   play_active_area.setPosition(ScaleTools::getScaledSize(p_active_pos, menu_background));
   play_active_area.setFillColor(hovered_button_colour);

   // Quit Button
   quit_text.setFont(FontManager::getInstance().getFont("Passport"));
   quit_text.setCharacterSize(ScaleTools::getScaledFont(250, menu_background));
   quit_text.setFillColor(regular_button_colour);
   quit_text.setString("QUIT");

   // Active Area - Quit
   sf::Vector2f q_active_area = { (1383/2), (393/2) };
   quit_active_area.setSize(q_active_area);
   sf::Vector2f q_active_pos = { 1192, 1658 };
   quit_active_area.setPosition(ScaleTools::getScaledSize(q_active_pos, menu_background));
   quit_active_area.setFillColor(regular_button_colour);
}

void Menu::setPositions() {
   sf::Vector2f title_pos = { 42, 70 };
   title.setPosition(ScaleTools::getScaledPosition(title_pos, menu_background));

   // Play Button
   sf::Vector2f play_btn_pos = { 933, 205 };
   play_background.setPosition(ScaleTools::getScaledPosition(play_btn_pos, menu_background));
   sf::Vector2f play_btn_text_pos = { 1423, 917 };
   play_text.setPosition(ScaleTools::getScaledPosition(play_btn_text_pos, menu_background));

   // Quit Button
   sf::Vector2f quit_btn_pos = { 1188, 1172 };
   quit_background.setPosition(ScaleTools::getScaledPosition(quit_btn_pos, menu_background));
   sf::Vector2f quit_btn_text_pos = { 1555, 1695 };
   quit_text.setPosition(ScaleTools::getScaledPosition(quit_btn_text_pos, menu_background));

   // HedgeHog
   sf::Vector2f hedgehog_pos = { 3135, 1429 };
   hedgehog.setPosition(ScaleTools::getScaledPosition(hedgehog_pos, menu_background));
}




