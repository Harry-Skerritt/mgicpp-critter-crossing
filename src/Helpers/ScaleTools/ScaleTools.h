//
// Created by Harry Skerritt on 25/10/2025.
//

#ifndef SCALETOOLS_H
#define SCALETOOLS_H

#include <SFML/Graphics.hpp>

namespace ScaleTools {

    /// <summary>
    /// Scales the unscaled_position based on the scale of scale_sprite
    /// </summary>
    /// <param name="unscaled_position"> A vector containing the unscaled position </param>
    /// <param name="scale_sprite"> A sprite which the position will scale around </param>
    sf::Vector2f getScaledPosition(sf::Vector2f& unscaled_position, sf::Sprite& scale_sprite);

    /// <summary>
    /// Scales the font_size based on the scale of scale_sprite
    /// </summary>
    /// <param name="font_size"> An int containing the unscaled font size </param>
    /// <param name="scale_sprite"> A sprite which the position will scale around </param>
    unsigned int getScaledFont(int font_size, sf::Sprite& scale_sprite);
}


#endif //SCALETOOLS_H
