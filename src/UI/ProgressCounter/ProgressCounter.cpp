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

void ProgressCounter::updateCount(int correct, int total) {
   correct_rounds = correct;
   total_rounds = total;

   updateText();
}

void ProgressCounter::draw(sf::RenderWindow &window) {
   if (is_visible)
   {
      window.draw(bubble_sprite);
      window.draw(label_text);
      window.draw(score_text);
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
   score_text.setString("0/0");

   positionText();
}

void ProgressCounter::positionText() {
   sf::Vector2f label_pos = {38, 32};
   label_text.setPosition(ScaleTools::getScaledPosition(label_pos, bubble_sprite));

   sf::Vector2f score_pos = {502, 32};
   score_text.setPosition(ScaleTools::getScaledPosition(score_pos, bubble_sprite));
}

void ProgressCounter::updateText() {
   score_text.setString(std::to_string(correct_rounds) + "/" + std::to_string(total_rounds));
   positionText();
}




