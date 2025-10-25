//
// Created by Harry Skerritt on 23/10/2025.
//

#include "Passport.h"

#include "../Game.h"
#include "../Manager/FontManager/FontManager.h"
#include "../Helpers/ScaleTools/ScaleTools.h"

Passport::Passport(const sf::Vector2f &position, const sf::Vector2f &size) {
    view.setSize(size);
    view.setCenter(size.x / 2.f, size.y / 2.f);

    view_rect = sf::FloatRect(position.x, position.y, size.x, size.y);

    setupBackground();
    setupText();

}

Passport::~Passport() = default;

// --- Setup ---
void Passport::setDataManager(PassportDataManager *manager) {
    data_manager = manager;
}

// --- Functionality ---
void Passport::initPassport(Character *character) {
    // Setup text
    display_name = data_manager->generateName();
    display_age = std::to_string(data_manager->generateAge());
    display_district = data_manager->generateDistrict();

    name_text.setString("Name: " + display_name);
    age_text.setString("Age: " + display_age);
    district_text.setString("District: " + display_district);
}

void Passport::draw(sf::RenderWindow &window, Game &game) {
    sf::Vector2f win_size = game.getDefaultView().getSize();
    view.setViewport({
        view_rect.left / win_size.x,
        view_rect.top / win_size.y,
        view_rect.width / win_size.x,
        view_rect.height / win_size.y
        });

    window.setView(view);

    window.draw(background);

    window.draw(name_text);
    window.draw(age_text);
    window.draw(district_text);

    window.setView(game.getDefaultView());
}





// --- PRIVATE ---
// Setup
bool Passport::setupBackground() {
    if (!background_texture.loadFromFile("../Data/Images/Passport.png")) {
        std::cerr << "Passport: Failed to load background texture" << std::endl;
        return false;
    }

    background.setTexture(background_texture);

    sf::Vector2f view_size = view.getSize();
    sf::Vector2f view_centre = view.getCenter();

    background.setOrigin(0.f, 0.f);
    background.setPosition(view_centre - view_size / 2.f);

    sf::Vector2u size = background_texture.getSize();
    std::cout << "Background texture size: " << size.x << ", " << size.y << std::endl;
    background.setScale(
        view_size.x / static_cast<float>(size.x),
        view_size.y / static_cast<float>(size.y));
}

bool Passport::setupText() {
    name_text.setFont(FontManager::getInstance().getFont("Jua"));
    name_text.setCharacterSize(ScaleTools::getScaledFont(unscaled_font_size, background));
    name_text.setFillColor(text_colour);
    name_text.setPosition(ScaleTools::getScaledPosition(name_text_pos_unscaled, background));


    age_text.setFont(FontManager::getInstance().getFont("Jua"));
    age_text.setCharacterSize(ScaleTools::getScaledFont(unscaled_font_size, background));
    age_text.setFillColor(text_colour);
    age_text.setPosition(ScaleTools::getScaledPosition(age_text_pos_unscaled, background));

    district_text.setFont(FontManager::getInstance().getFont("Jua"));
    district_text.setCharacterSize(ScaleTools::getScaledFont(unscaled_font_size, background));
    district_text.setFillColor(text_colour);
    district_text.setPosition(ScaleTools::getScaledPosition(district_text_pos_unscaled, background));
}






