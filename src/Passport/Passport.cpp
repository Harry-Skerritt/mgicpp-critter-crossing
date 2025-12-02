//
// Created by Harry Skerritt on 23/10/2025.
//

#include "Passport.h"

#include "../Game.h"
#include "../Manager/FontManager/FontManager.h"
#include "../Helpers/ScaleTools/ScaleTools.h"

Passport::Passport(const sf::Vector2f &position, const sf::Vector2f &size)
{

    view.setSize(size);
    view.setCenter(size.x / 2.f, size.y / 2.f);
    view_rect = sf::FloatRect(position.x, position.y, size.x, size.y);
    view.zoom(zoom);

    if (!setupBackground())
    {
        std::cerr << "Failed to setup background" << std::endl;
    }

    setupText();

    if (!setupPhoto())
    {
        std::cerr << "Failed to setup photo" << std::endl;
    }

    // Character
    passport_character = std::make_unique<Character>(
        ScaleTools::getScaledPosition(character_unscaled_pos, background),
        ScaleTools::getScaledSize(character_unscaled_size, background));

    stamps_loaded = loadStamps();

}

Passport::~Passport() = default;

// --- Setup ---
void Passport::setDataManager(PassportDataManager *manager)
{
    data_manager = manager;
}

// --- State Manipulators ---
void Passport::setPassportStamp(PassportStampValue value)
{
    current_stamp_state = value;

    if (current_stamp_state == PassportStampValue::APPROVE)
    {
        stamp_sprite.setTexture(approve_stamp_texture);
        stamp_sprite.setColor(sf::Color::White);
    }

    if (current_stamp_state == PassportStampValue::REJECT)
    {
        stamp_sprite.setTexture(deny_stamp_texture);
        stamp_sprite.setColor(sf::Color::White);
    }

    if (current_stamp_state == PassportStampValue::NONE) {
        stamp_sprite.setColor(sf::Color::Transparent);
    }

    positionStamp();
}

void Passport::setZoom(float factor) {
    zoom = factor;
    view.zoom(zoom);
}

float Passport::getZoom() const {
    return zoom;
}

void Passport::setSize(sf::Vector2f size) {
    view.setSize(size);

    sf::FloatRect new_view_rect = {
        view_rect.left,
        view_rect.top,
        size.x,
        size.y
    };
    view_rect = new_view_rect;
}

sf::Vector2f Passport::getSize() const {
    return view.getSize();
}

std::string Passport::getPassportStampValue() const {
    switch (current_stamp_state)
    {
        case (PassportStampValue::APPROVE):
            return "Approve";
        case (PassportStampValue::REJECT):
            return "Reject";
        case (PassportStampValue::NONE):
            return "None";
        default:
            return "Default";
    }
}


// --- Functionality ---
void Passport::initPassport(const CharacterAssetData& data)
{
    asset_data = std::make_unique<CharacterAssetData>(data);

    if (asset_data == nullptr)
    {
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

void Passport::resetPassport(sf::Vector2f& start_pos)
{
    is_visible = true;
    current_stamp_state = PassportStampValue::NONE;
    current_state = PassportState::CLOSED;
    passport_stamped = false;
    can_be_dragged = true;
    setDragPosition(start_pos);
}


void Passport::openPassport()
{
    if (current_state == PassportState::CLOSED) {
        current_state = PassportState::OPEN;
    }
}

void Passport::closePassport()
{
    if (current_state == PassportState::OPEN) {
        current_state = PassportState::CLOSED;
    }
}

sf::FloatRect Passport::getPassportBounds() const {
    return view_rect;
}

sf::Vector2f Passport::getPassportPosition() const {
    return {view_rect.left, view_rect.top};
}

void Passport::setDragPosition(const sf::Vector2f &position) {
    view_rect.left = position.x;
    view_rect.top = position.y;
}


void Passport::draw(sf::RenderWindow &window, Game &game)
{
    if (is_visible)
    {
        sf::Vector2f win_size = game.getDefaultView().getSize();
        view.setViewport({
            view_rect.left / win_size.x,
            view_rect.top / win_size.y,
            view_rect.width / win_size.x,
            view_rect.height / win_size.y
            });

        window.setView(view);

        if (current_state == PassportState::CLOSED)
        {
            window.draw(closed_passport_sprite);
        }
        else if (current_state == PassportState::OPEN)
        {
            window.draw(background);

            preparePhoto();
            window.draw(photo_sprite);


            window.draw(name_text);
            window.draw(age_text);
            window.draw(district_text);

            window.draw(stamp_sprite);
        }

        window.setView(game.getDefaultView());
    }

}


// --- PRIVATE ---
// Setup
bool Passport::setupBackground()
{
    // Open Background
    if (!background_texture.loadFromFile("../Data/Images/Passport/Passport.png"))
    {
        std::cerr << "Passport: Failed to load background texture" << std::endl;
        return false;
    }

    background.setTexture(background_texture);
    ScaleTools::scaleToView(background, view);

    // Closed Background
    if (!closed_passport_texture.loadFromFile("../Data/Images/Passport/ClosedPassport.png"))
    {
        std::cerr << "Passport: Failed to load closed passport texture" << std::endl;
        return false;
    }
    closed_passport_sprite.setTexture(closed_passport_texture);
    ScaleTools::scaleToView(closed_passport_sprite, view, false, false);
    return true;
}

void Passport::setupText()
{
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

bool Passport::setupPhoto()
{
    sf::Vector2f photo_size = ScaleTools::getScaledSize(character_unscaled_size, background);
    if (!photo_texture.create(photo_size.x, photo_size.y))
    {
        std::cerr << "Failed to create photo_texture" << std::endl;
        return false;
    }

    photo_sprite.setOrigin(0.f, 0.f);
    photo_sprite.setPosition(ScaleTools::getScaledPosition(character_unscaled_pos, background));

    return true;
}

void Passport::preparePhoto()
{
    passport_character->loadCharacter(*asset_data);
    photo_texture.clear(sf::Color::Transparent);
    passport_character->drawInPassport(photo_texture);
    photo_texture.display();
    photo_sprite.setTexture(photo_texture.getTexture());
}

bool Passport::loadStamps()
{
    if (!approve_stamp_texture.loadFromFile("../Data/Images/Passport/Stamps/ApproveStamp.png"))
    {
        std::cerr << "Passport: Failed to load approve stamp texture" << std::endl;
        return false;
    }

    if (!deny_stamp_texture.loadFromFile("../Data/Images/Passport/Stamps/DenyStamp.png"))
    {
        std::cerr << "Passport: Failed to load deny stamp texture" << std::endl;
        return false;
    }

    return true;
}

void Passport::positionStamp() {
    stamp_sprite.setScale(0.5f, 0.5f);
    stamp_sprite.setPosition(ScaleTools::getScaledPosition(stamp_pos_unscaled, background));
}









