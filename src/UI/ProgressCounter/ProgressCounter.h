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
  void updateCount(int correct, int total, int lives_left, int lives_total);
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

  // Background
  sf::Texture bubble_texture;
  sf::Sprite bubble_sprite;

  // Score
  sf::Text label_text;
  sf::Text score_text;

  int total_rounds;
  int correct_rounds;

  // Lives
  sf::Text lives_label;
  sf::Text lives_text;

  int total_lives;
  int lives_remaining;

};



#endif //PROGRESSCOUNTER_H
