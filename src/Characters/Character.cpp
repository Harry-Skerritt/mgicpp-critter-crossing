//
// Created by Harry Skerritt on 22/10/2025.
//

#include "Character.h"

Character::Character(const sf::Vector2f &position, const sf::Vector2f &size) {
    temp_shape.setSize(size);
    temp_shape.setFillColor(sf::Color(200, 180, 150));
    temp_shape.setOrigin(size / 2.f);

    view.setSize(size);
    view.setCenter(0.f, 0.f);

    view_rect = sf::FloatRect(position.x, position.y, size.x, size.y);
}

Character::~Character() = default;

void Character::loadCharacter(std::array<sf::Texture*, 4> textures, CreatureType type) {
    character_loaded = false;

    // Load textures from array
    body_texture = textures[0];
    eye_texture = textures[1];
    glasses_texture = textures[2];
    hat_texture = textures[3];

    if (body_texture == nullptr || eye_texture == nullptr || glasses_texture == nullptr || hat_texture == nullptr) {
        return;
    }

    std::cout << "Current CreatureType: " << creatureTypeToString(type) << std::endl;

    // Set Body
    body_sprite.setTexture(*body_texture);
    setScaleAndOrigin(&body_sprite);
    sf::Vector2f body_offset = (SPRITE_OFFSETS.at(type).body_offset) * body_sprite.getScale().x;
    sf::Vector2f body_base_pos = {0.f, 0.f};
    sf::Vector2f body_pos = body_base_pos + body_offset;
    body_sprite.setPosition(body_pos);

    eye_sprite.setTexture(*eye_texture);
    setScaleAndOrigin(&eye_sprite);
    sf::Vector2f eye_offset = (SPRITE_OFFSETS.at(type).eyes_offset) * eye_sprite.getScale().x;
    eye_sprite.setPosition(body_pos + eye_offset);

    glasses_sprite.setTexture(*glasses_texture);
    setScaleAndOrigin(&glasses_sprite);
    glasses_sprite.setPosition(body_pos + eye_offset);

    hat_sprite.setTexture(*hat_texture);
    setScaleAndOrigin(&hat_sprite);
    sf::Vector2f hat_offset = (SPRITE_OFFSETS.at(type).hat_offset) * hat_sprite.getScale().x;
    hat_sprite.setPosition(body_pos + hat_offset);

    character_loaded = true;
}

void Character::draw(sf::RenderWindow &window) {
    sf::Vector2u winSize = window.getSize();
    view.setViewport({
        view_rect.left / winSize.x,
        view_rect.top / winSize.y,
        view_rect.width / winSize.x,
        view_rect.height / winSize.y
        });

    window.setView(view);

   // Background
    window.draw(temp_shape);

    if (character_loaded) {
        window.draw(body_sprite);
        window.draw(eye_sprite);
        window.draw(glasses_sprite);
        window.draw(hat_sprite);
    }

    window.setView(window.getDefaultView());
}

void Character::setViewCentre(const sf::Vector2f &centre) {
    view.setCenter(centre);
}


// --- PRIVATE ---
void Character::setScaleAndOrigin(sf::Sprite* sprite) {
    // Handle Scale
    sf::Vector2f view_size = view.getSize();
    sf::FloatRect sprite_bounds = sprite->getLocalBounds();

    float scaleX = view_size.x / sprite_bounds.width;
    float scaleY = view_size.y / sprite_bounds.height;

    float uniform_scale = std::min(scaleX, scaleY);
    sprite->setScale(uniform_scale, uniform_scale);

    // Handle Origin
    sprite->setOrigin(sprite_bounds.width / 2.f, sprite_bounds.height / 2.f);
}



std::string Character::creatureTypeToString(CreatureType type) {
    switch (type) {
        case(CreatureType::BEAR):
            return "Bear";
        case(CreatureType::CHICKEN):
            return "Chicken";
        case(CreatureType::FOX):
            return "Fox";
        case(CreatureType::HEDGEHOG):
            return "Hedgehog";
        case(CreatureType::REINDEER):
            return "Reindeer";
        case(CreatureType::SKUNK):
            return "Skunk";
        case(CreatureType::SQUIRREL):
            return "Squirrel";
        case(CreatureType::WOLF):
            return "Wolf";
        case(CreatureType::NONE):
            return "None";
        default:
            return "Hmm...";
    }
}

// Debug
// Todo: Remove before building
void Character::drawBoundingBoxes(sf::RenderWindow &window) {
    if (!character_loaded) return;

    auto drawBox = [&](sf::Sprite& sprite, sf::Color color){
        sf::FloatRect bounds = sprite.getGlobalBounds();
        sf::RectangleShape rect;
        rect.setSize({bounds.width, bounds.height});
        rect.setPosition(bounds.left, bounds.top);
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(color);
        rect.setOutlineThickness(2.f);
        window.draw(rect);
    };

    drawBox(body_sprite, sf::Color::Red);
    drawBox(eye_sprite, sf::Color::Green);
    drawBox(glasses_sprite, sf::Color::Blue);
    drawBox(hat_sprite, sf::Color::Yellow);

    auto drawCenter = [&](sf::Sprite& sprite, sf::Color color){
        sf::CircleShape marker(5.f);
        marker.setOrigin(5.f, 5.f);
        marker.setFillColor(color);
        marker.setPosition(sprite.getPosition());
        window.draw(marker);
    };

    drawCenter(body_sprite, sf::Color::Red);
    drawCenter(eye_sprite, sf::Color::Green);
    drawCenter(glasses_sprite, sf::Color::Blue);
    drawCenter(hat_sprite, sf::Color::Yellow);
}
