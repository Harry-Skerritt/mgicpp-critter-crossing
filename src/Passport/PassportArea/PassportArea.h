//
// Created by Harry Skerritt on 29/11/2025.
//

#ifndef PASSPORTAREA_H
#define PASSPORTAREA_H

#include <iostream>

#include <SFML/Graphics.hpp>

#include "../../Helpers/ScaleTools/ScaleTools.h"
#include "../Passport.h"

enum class SlotType { NONE, PASSPORT, RETURN };

class PassportArea {
// Funcs
public:
  PassportArea();
  ~PassportArea() = default;

  void init(std::string texture_loc);
  void draw(sf::RenderWindow& window);

  bool isPassportInArea(Passport* passport);

  sf::Vector2f getPassportLockPosition();

  void setVisible(bool visible);
  bool isVisible() const { return is_visible; };

  void setSlotType(SlotType slot_type);
  SlotType getSlotType() const { return passport_slot_type; }

  void setAreaPosition(sf::Vector2f& pos, sf::Sprite& background_sprite);

private:

  bool loadTextures(std::string texture_loc);

// Vars
public:
private:
  sf::Texture passport_area_texture;
  sf::Sprite passport_area;

  sf::Vector2f passport_lock_point_offset = { 20, 20 };

  SlotType passport_slot_type = SlotType::NONE;

  bool is_visible = false;

};



#endif //PASSPORTAREA_H
