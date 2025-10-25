//
// Created by Harry Skerritt on 25/10/2025.
//

#include "ScaleTools.h"

#include <cmath>

sf::Vector2f ScaleTools::getScaledPosition(sf::Vector2f &unscaled_position, sf::Sprite &scale_sprite) {
    sf::Vector2f sprite_scale = scale_sprite.getScale();
    return {
        scale_sprite.getPosition().x + unscaled_position.x * sprite_scale.x,
        scale_sprite.getPosition().y + unscaled_position.y * sprite_scale.y};
}

unsigned int ScaleTools::getScaledFont(int font_size, sf::Sprite &scaled_sprite) {
    sf::Vector2f sprite_scale = scaled_sprite.getScale();
    return static_cast<unsigned int>(font_size) * sprite_scale.y;
}


void ScaleTools::scaleToView(sf::Sprite& sprite_to_scale, const sf::View &view, bool set_centre_origin, bool scale_uniform) {
    sf::Vector2f view_size = view.getSize();
    sf::Vector2f view_centre = view.getCenter();
    sf::FloatRect sprite_bounds = sprite_to_scale.getLocalBounds();

    if (set_centre_origin) {
        sprite_to_scale.setOrigin(sprite_bounds.width / 2.f, sprite_bounds.height / 2.f);
    } else {
        sprite_to_scale.setOrigin(0.f, 0.f);
        sprite_to_scale.setPosition(view_centre - view_size / 2.f);
    }

    float scale_x = view_size.x / sprite_bounds.width;
    float scale_y = view_size.y / sprite_bounds.height;

    if (scale_uniform) {
        float uniform_scale = std::min(scale_x, scale_y);
        sprite_to_scale.setScale(uniform_scale, uniform_scale);
    } else {
        sprite_to_scale.setScale(scale_x, scale_y);
    }


}

