//
// Created by Harry Skerritt on 23/10/2025.
//

#include "Passport.h"

#include "../Game.h"
#include "../Manager/FontManager/FontManager.h"
#include "../Helpers/ScaleTools/ScaleTools.h"

Passport::Passport(const sf::Vector2f &position, const sf::Vector2f &size){

    view.setSize(size);
    view.setCenter(size.x / 2.f, size.y / 2.f);
    view_rect = sf::FloatRect(position.x, position.y, size.x, size.y);

    if (!setupBackground()) {
        std::cerr << "Failed to setup background" << std::endl;
    }

    setupText();

    if (!setupPhoto()) {
        std::cerr << "Failed to setup photo" << std::endl;
    }

    // Character
    passport_character = std::make_unique<Character>(
        ScaleTools::getScaledPosition(character_unscaled_pos, background),
        ScaleTools::getScaledSize(character_unscaled_size, background));

}

Passport::~Passport() = default;

// --- Setup ---
void Passport::setDataManager(PassportDataManager *manager) {
    data_manager = manager;
}

// --- Functionality ---
void Passport::initPassport(const CharacterAssetData& data) {
    asset_data = std::make_unique<CharacterAssetData>(data);

    if (asset_data == nullptr) {
        // Gen new data
        std::cerr << "Passport::initPassport: asset data is null" << std::endl;
        asset_data = nullptr;
    }

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

    preparePhoto();
    window.draw(photo_sprite);


    window.draw(name_text);
    window.draw(age_text);
    window.draw(district_text);

    window.setView(game.getDefaultView());
}

const sf::View& Passport::getDefaultView() {
    return view;
}






// --- PRIVATE ---
// Setup
bool Passport::setupBackground() {
    if (!background_texture.loadFromFile("../Data/Images/Passport.png")) {
        std::cerr << "Passport: Failed to load background texture" << std::endl;
        return false;
    }

    background.setTexture(background_texture);
    ScaleTools::scaleToView(background, view);
    return true;
}

void Passport::setupText() {
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

bool Passport::setupPhoto() {
    sf::Vector2f photo_size = ScaleTools::getScaledSize(character_unscaled_size, background);
    if (!photo_texture.create(photo_size.x, photo_size.y)){
        std::cerr << "Failed to create photo_texture" << std::endl;
        return false;
    }

    photo_sprite.setOrigin(0.f, 0.f);
    photo_sprite.setPosition(ScaleTools::getScaledPosition(character_unscaled_pos, background));

    return true;
}

void Passport::preparePhoto() {
    passport_character->loadCharacter(*asset_data);
    passport_character->drawInPassport(photo_texture);
    photo_texture.display();
    photo_sprite.setTexture(photo_texture.getTexture());
}







