//
// Created by Harry Skerritt on 29/11/2025.
//

#include "PassportArea.h"

 PassportArea::PassportArea() {  }


void PassportArea::init(sf::Sprite& background_sprite)
{
   loadTextures(background_sprite);
}

void PassportArea::draw(sf::RenderWindow& window)
{
   if (is_visible) {
     window.draw(passport_area);

     sf::RectangleShape rect;
     rect.setFillColor(sf::Color::White);
     rect.setSize({10.f, 10.f});
     sf::Vector2f pos = passport_area.getPosition() + passport_lock_point_offset;
     rect.setPosition(pos);
     window.draw(rect);
   }

}


bool PassportArea::isPassportInArea(sf::Vector2f passport_position)
{
   if (passport_area.getGlobalBounds().contains(passport_position)) {
     return true;
   }
   return false;
}

sf::Vector2f PassportArea::getPassportLockPosition() {
   sf::Vector2f pos = passport_area.getPosition() + passport_lock_point_offset;
   return pos;
 }


void PassportArea::setVisible(bool visible)
{
  is_visible = visible;
}

// --- PRIVATE ---
bool PassportArea::loadTextures(sf::Sprite& background_sprite) {
   if (!passport_area_texture.loadFromFile("../Data/Images/PassportSlot.png"))
   {
     std::cout << "Passport slot texture failed to load!" << std::endl;
     return false;
   }
   passport_area.setTexture(passport_area_texture);
   passport_area.setScale(0.5f, 0.5f);
   passport_area.setPosition(ScaleTools::getScaledPosition(passport_area_unscaled_pos, background_sprite));
 }




