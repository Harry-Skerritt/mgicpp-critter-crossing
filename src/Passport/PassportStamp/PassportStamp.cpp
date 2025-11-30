//
// Created by Harry Skerritt on 28/11/2025.
//

#include "PassportStamp.h"

#include "../../Helpers/ScaleTools/ScaleTools.h"

#include <iostream>

PassportStamp::PassportStamp() {
   setupTextures();
   setupText();
   setupActiveAreas();
}

void PassportStamp::init()
{

}

void PassportStamp::setPassport(Passport *passport) {
   this->passport = passport;
}

void PassportStamp::handleMouseHover(sf::Vector2f mouse_pos)
{
   // Mouse Hovering
   if (approve_active_area.getGlobalBounds().contains(mouse_pos))
   {
      approve_text.setFillColor(approve_hover_colour);
      approve_hovered = true;
   }
   else
   {
      approve_text.setFillColor(default_button_colour);
      approve_hovered = false;
   }


   if (deny_active_area.getGlobalBounds().contains(mouse_pos))
   {
      deny_text.setFillColor(deny_hover_colour);
      deny_hovered = true;
   }
   else
   {
      deny_text.setFillColor(default_button_colour);
      deny_hovered = false;
   }
}

void PassportStamp::onMouseClick() {
   if (approve_hovered)
   {
      std::cout << "Approve Passport" << std::endl;
      is_visible = false;
      if (passport != nullptr)
      {
         //passport->setPassportState(PassportState::CLOSED);
         passport->setPassportStamp(PassportStampValue::APPROVE);
         passport->setCanBeDragged(true);
      }
   }

   if (deny_hovered)
   {
      std::cout << "Deny Passport" << std::endl;
      is_visible = false;
      if (passport != nullptr)
      {
         //passport->setPassportState(PassportState::CLOSED);
         passport->setPassportStamp(PassportStampValue::REJECT);
         passport->setCanBeDragged(true);
      }
   }
}



void PassportStamp::draw(sf::RenderWindow& window) {
   if (is_visible) {
      window.draw(button_background_sprite);
      window.draw(approve_button_sprite);
      window.draw(deny_button_sprite);
      window.draw(approve_text);
      window.draw(deny_text);

      window.draw(approve_active_area);
      window.draw(deny_active_area);
   }
}

void PassportStamp::showStampUI(bool visible, sf::Vector2f mouse_pos, sf::Vector2f window_size) {
   is_visible = visible;

   float button_box_x = button_background_sprite.getGlobalBounds().getSize().x;
   float button_box_y = button_background_sprite.getGlobalBounds().getSize().y;

   float pos_x, pos_y;

   pos_x = mouse_pos.x;
   pos_y = mouse_pos.y;

   if ((mouse_pos.x + button_box_x + BORDER_MARGIN) > window_size.x)
   {
      std::cout << "TOO CLOSE TO WINDOW EDGE X" << std::endl;
      pos_x = mouse_pos.x - (button_box_x - BORDER_MARGIN);
   }

   if ((mouse_pos.y + button_box_y + BORDER_MARGIN) > window_size.y)
   {
      std::cout << "TOO CLOSE TO WINDOW EDGE Y" << std::endl;
      pos_y = mouse_pos.y - (button_box_y - BORDER_MARGIN);
   }

   button_box_position = sf::Vector2f(pos_x, pos_y);

   setPositions();
}

// --- PRIVATE ---
bool PassportStamp::setupTextures() {
   // Background
   if (!button_background_texture.loadFromFile("../Data/Images/ButtonBackground.png"))
   {
      std::cout << "Error loading button background" << std::endl;
      return false;
   }
   button_background_sprite.setTexture(button_background_texture);

   // Buttons
   if (!plank_texture_1.loadFromFile("../Data/Images/Planks/WoodPlank2.png"))
   {
      std::cout << "Error loading plank texture 2" << std::endl;
      return false;
   }
   approve_button_sprite.setTexture(plank_texture_1);

   if (!plank_texture_2.loadFromFile("../Data/Images/Planks/WoodPlank3.png"))
   {
      std::cout << "Error loading plank texture 3" << std::endl;
      return false;
   }

   deny_button_sprite.setTexture(plank_texture_2);

   if (setPositions()) {
      return true;
   }

   return false;

}

bool PassportStamp::setupText() {
   approve_text.setColor(default_button_colour);
   approve_text.setString("Approve");
   approve_text.setFont(FontManager::getInstance().getFont("Passport"));
   approve_text.setCharacterSize(ScaleTools::getScaledFont(TEXT_SIZE, button_background_sprite));

   deny_text.setColor(default_button_colour);
   deny_text.setString("Deny");
   deny_text.setFont(FontManager::getInstance().getFont("Passport"));
   deny_text.setCharacterSize(ScaleTools::getScaledFont(TEXT_SIZE, button_background_sprite));
}

bool PassportStamp::setPositions() {
   // Background
   button_background_sprite.setScale(0.5f, 0.5f);
   button_background_sprite.setPosition(button_box_position);

   // Button - Approve
   approve_button_sprite.setScale(0.32f, 0.32f);
   approve_button_sprite.setPosition(
      ScaleTools::getScaledPosition(approve_button_unscaled_position, button_background_sprite));

   approve_text.setPosition(
      ScaleTools::getScaledPosition(approve_text_unscaled_position, button_background_sprite));

   approve_active_area.setPosition(
      ScaleTools::getScaledPosition(approve_area_unscaled_pos, button_background_sprite));

   // Button - Deny
   deny_button_sprite.setScale(0.32f, 0.32f);
   deny_button_sprite.setPosition(
      ScaleTools::getScaledPosition(deny_button_unscaled_position, button_background_sprite));

   deny_text.setPosition(
      ScaleTools::getScaledPosition(deny_text_unscaled_position, button_background_sprite));

   deny_active_area.setPosition(
      ScaleTools::getScaledPosition(deny_area_unscaled_pos, button_background_sprite));
}

bool PassportStamp::setupActiveAreas() {
   approve_active_area.setSize(
      ScaleTools::getScaledSize(active_area_size, button_background_sprite));
   approve_active_area.setFillColor(sf::Color::Transparent);
   approve_active_area.setPosition(
      ScaleTools::getScaledPosition(approve_area_unscaled_pos, button_background_sprite));

   deny_active_area.setSize(
      ScaleTools::getScaledSize(active_area_size, button_background_sprite));
   deny_active_area.setFillColor(sf::Color::Transparent);
   deny_active_area.setPosition(
      ScaleTools::getScaledPosition(deny_area_unscaled_pos, button_background_sprite));
}



