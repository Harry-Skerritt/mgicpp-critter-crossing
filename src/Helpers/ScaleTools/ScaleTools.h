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
    /// Scales the unscaled_size based on the scale of scale_sprite
    /// </summary>
    /// <param name="unscaled_size"> A vector containing the unscaled size </param>
    /// <param name="scale_sprite"> A sprite which the position will scale around </param>
    sf::Vector2f getScaledSize(sf::Vector2f& unscaled_size, sf::Sprite& scale_sprite);


    /// <summary>
    /// Scales the font_size based on the scale of scale_sprite
    /// </summary>
    /// <param name="font_size"> An int containing the unscaled font size </param>
    /// <param name="scale_sprite"> A sprite which the position will scale around </param>
    unsigned int getScaledFont(int font_size, sf::Sprite& scale_sprite);

    /// <summary>
    /// Scale an object (sprite) to fill the view
    /// </summary>
    /// <param name="sprite_to_scale"> The object to scale </param>
    /// <param name="view"> The view it needs to fill </param>
    /// <param name="set_centre_origin"> Set the origin to the centre as opposed to the top left </param>
    /// <param name="scale_uniform"> Whether to scale uniformly or not </param>
    void scaleToView(sf::Sprite& sprite_to_scale, const sf::View& view, bool set_centre_origin = false, bool scale_uniform = true);

}


#endif //SCALETOOLS_H
