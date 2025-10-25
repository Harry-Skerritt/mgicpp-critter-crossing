//
// Created by Harry Skerritt on 25/10/2025.
//

#include "ScaleTools.h"

sf::Vector2f ScaleTools::getScaledPosition(sf::Vector2f &unscaled_position, sf::Sprite &scale_sprite) {
    sf::Vector2f sprite_scale = scaled_sprite.getScale();
    return {
        scaled_sprite.getPosition().x + unscaled_position.x * sprite_scale.x,
        scaled_sprite.getPosition().y + unscaled_position.y * sprite_scale.y};
}

unsigned int ScaleTools::getScaledFont(int font_size, sf::Sprite &scaled_sprite) {
    sf::Vector2f sprite_scale = scaled_sprite.getScale();
    return static_cast<unsigned int>(font_size) * sprite_scale.y;
}
