//
// Created by Harry Skerritt on 29/11/2025.
//

#ifndef PASSPORTAREA_H
#define PASSPORTAREA_H

#include <iostream>

#include <SFML/Graphics.hpp>

#include "../../Helpers/ScaleTools/ScaleTools.h"


class PassportArea {
// Funcs
public:
  PassportArea();
  ~PassportArea() = default;

  void init(sf::Sprite& background_sprite);
  void update();
  void draw(sf::RenderWindow& window);

  bool isPassportInArea(sf::Vector2f passport_position);

  sf::Vector2f getPassportLockPosition();

  void setVisible(bool visible);
  bool isVisible() { return is_visible; };

private:

  bool loadTextures(sf::Sprite& background_sprite);

// Vars
public:
private:
  sf::Texture passport_area_texture;
  sf::Sprite passport_area;
  sf::Vector2f passport_area_unscaled_pos = { 2198, 89 };

  sf::Vector2f passport_lock_point_offset = { 50, 50 };

  bool is_visible = false;

};



#endif //PASSPORTAREAS_H
