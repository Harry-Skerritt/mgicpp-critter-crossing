//
// Created by Harry Skerritt on 02/12/2025.
//

#include "ProgressCounter.h"

#include "../../Helpers/ScaleTools/ScaleTools.h"
#include "../../Manager/FontManager/FontManager.h"

#include <iostream>

ProgressCounter::ProgressCounter() {  }


void ProgressCounter::init(sf::Vector2f pos, sf::Sprite* background) {
   background_sprite = background;

   loadSprites(pos);
   setupText();
}

void ProgressCounter::updateCount(int correct, int total, int lives_left, int lives_total) {
   correct_rounds = correct;
   total_rounds = total;
   lives_remaining = lives_left;
   total_lives = lives_total;

   updateText();
}

void ProgressCounter::draw(sf::RenderWindow &window) {
   if (is_visible)
   {
      window.draw(bubble_sprite);
      window.draw(label_text);
      window.draw(score_text);
      window.draw(lives_label);
      window.draw(lives_text);
   }
}

// --- Private ---
void ProgressCounter::loadSprites(sf::Vector2f pos) {
   if (!bubble_texture.loadFromFile("../Data/Images/Planks/UIBubble.png")) {
      std::cerr << "Could not load UIBubble.png" << std::endl;
   }
   bubble_sprite.setTexture(bubble_texture);
   bubble_sprite.setScale(0.5f, 0.5f);
   bubble_sprite.setPosition(pos.x, pos.y);
}

void ProgressCounter::setupText() {
   label_text.setFont(FontManager::getInstance().getFont("Passport"));
   label_text.setCharacterSize(ScaleTools::getScaledFont(100, *background_sprite));
   label_text.setString("Correct: ");

   score_text.setFont(FontManager::getInstance().getFont("Passport"));
   score_text.setCharacterSize(ScaleTools::getScaledFont(100, *background_sprite));
   score_text.setString("0/1");

   lives_label.setFont(FontManager::getInstance().getFont("Passport"));
   lives_label.setCharacterSize(ScaleTools::getScaledFont(100, *background_sprite));
   lives_label.setString("Lives: ");

   lives_text.setFont(FontManager::getInstance().getFont("Passport"));
   lives_text.setCharacterSize(ScaleTools::getScaledFont(100, *background_sprite));
   lives_text.setString("3/3");

   positionText();
}

void ProgressCounter::positionText() {
   sf::Vector2f label_pos = {38, 32};
   label_text.setPosition(ScaleTools::getScaledPosition(label_pos, bubble_sprite));

   sf::Vector2f score_pos = {502, 32};
   score_text.setPosition(ScaleTools::getScaledPosition(score_pos, bubble_sprite));

   sf::Vector2f lives_pos = {160 , 223};
   lives_label.setPosition(ScaleTools::getScaledPosition(lives_pos, bubble_sprite));

   sf::Vector2f lives_text_pos = {502, 223};
   lives_text.setPosition(ScaleTools::getScaledPosition(lives_text_pos, bubble_sprite));
}

void ProgressCounter::updateText() {
   score_text.setString(std::to_string(correct_rounds) + "/" + std::to_string(total_rounds));
   lives_text.setString(std::to_string(lives_remaining) + "/" + std::to_string(total_lives));
   positionText();
}




