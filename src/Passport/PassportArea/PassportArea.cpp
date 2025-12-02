//
// Created by Harry Skerritt on 29/11/2025.
//

#include "PassportArea.h"

 PassportArea::PassportArea() {  }


void PassportArea::init(std::string texture_loc)
{
   loadTextures(texture_loc);
}

void PassportArea::draw(sf::RenderWindow& window)
{
   if (is_visible) {
     window.draw(passport_area);
   }

}


bool PassportArea::isPassportInArea(Passport* passport) const {
   if (passport_area.getGlobalBounds().contains(passport->getPassportPosition())) {
     return true;
   }
   return false;
}

sf::Vector2f PassportArea::getPassportLockPosition() const {
   sf::Vector2f pos = passport_area.getPosition() + passport_lock_point_offset;
   return pos;
 }


void PassportArea::setVisible(bool visible)
{
  is_visible = visible;
}

void PassportArea::setSlotType(SlotType slot_type)
{
   passport_slot_type = slot_type;
}


// --- PRIVATE ---
bool PassportArea::loadTextures(std::string texture_loc) {
   if (!passport_area_texture.loadFromFile(texture_loc))
   {
     std::cout << "Passport slot texture failed to load!" << std::endl;
     return false;
   }
   passport_area.setTexture(passport_area_texture);
   passport_area.setScale(0.5f, 0.5f);
   return true;
 }

void PassportArea::setAreaPosition(sf::Vector2f &pos, sf::Sprite& background_sprite)
{
   passport_area.setPosition(ScaleTools::getScaledPosition(pos, background_sprite));

}





