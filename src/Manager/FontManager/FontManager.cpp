//
// Created by Harry Skerritt on 24/10/2025.
//

#include "FontManager.h"

#include <iostream>

FontManager &FontManager::getInstance() {
    static FontManager instance;
    return instance;
}

FontManager::FontManager() = default;
FontManager::~FontManager() = default;

bool FontManager::loadFont(const std::string &font_name, const std::string &file_name, const std::string &resource_location) {
    std::shared_ptr<sf::Font> font = std::make_shared<sf::Font>();
    std::string font_path = resource_location + file_name;

    if (font_name.empty()) {
        std::cout << "FontManager: font_name is empty" << std::endl;
        return false;
    }

    if (!font->loadFromFile(font_path)) {
        std::cout << "FontManager: Error loading font: " << font_name << std::endl;
        return false;
    }

    fonts.insert({font_name, font});
    return true;
}

sf::Font& FontManager::getFont(const std::string &font_name) {
    if (font_name.empty()) {
        throw std::invalid_argument("FontManager: font_name is empty");
    }


    auto iterator = fonts.find(font_name);
    if (iterator == fonts.end() || !(iterator->second)) {
        throw std::invalid_argument("FontManager: font not found: " + font_name);
    }

    return *(iterator->second);

}



