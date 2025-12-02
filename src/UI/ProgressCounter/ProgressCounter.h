//
// Created by Harry Skerritt on 02/12/2025.
//

#ifndef PROGRESSCOUNTER_H
#define PROGRESSCOUNTER_H

#include <SFML/Graphics.hpp>

class ProgressCounter {
// Funcs
public:
  ProgressCounter();
  ~ProgressCounter() = default;

  void init(sf::Vector2f pos, sf::Sprite* background);
  void updateCount(int correct, int total);
  void draw(sf::RenderWindow& window);

  void setVisible(bool visible) { is_visible = visible; }
  bool isVisible() const { return is_visible; }

private:

  void loadSprites(sf::Vector2f pos);
  void setupText();
  void positionText();
  void updateText();


// Vars
public:
private:

  bool is_visible = true;

  sf::Sprite* background_sprite;

  sf::Text label_text;
  sf::Text score_text;

  sf::Texture bubble_texture;
  sf::Sprite bubble_sprite;

  int total_rounds;
  int correct_rounds;

};



#endif //PROGRESSCOUNTER_H
