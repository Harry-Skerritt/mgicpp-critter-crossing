//
// Created by Harry Skerritt on 24/10/2025.
//

#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class FontManager {
// Funcs
public:
    static FontManager& getInstance();

    // Member funcs
    FontManager(const FontManager&) = delete;
    FontManager& operator=(const FontManager&) = delete;
    FontManager(FontManager&&) = delete;
    FontManager& operator=(FontManager&&) = delete;

    bool loadFont(const std::string& font_name, const std::string& file_name, const std::string& resource_location = "../Data/Fonts/");
    sf::Font& getFont(const std::string& name);


private:
    FontManager();
    ~FontManager();

// Vars
public:

private:
    std::map<std::string, std::shared_ptr<sf::Font>> fonts;

};



#endif //FONTMANAGER_H
