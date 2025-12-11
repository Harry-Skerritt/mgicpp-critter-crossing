//
// Created by Harry Skerritt on 30/11/2025.
//

#ifndef FEEDBACKFADE_H
#define FEEDBACKFADE_H

#include <SFML/Graphics.hpp>
#include <string>

enum class FadeState { FADE_IN, FADE_OUT, HOLD, NONE };

class FeedbackFade {
// Funcs
public:
  FeedbackFade();
  ~FeedbackFade() = default;

  void init(std::string texture_loc, float fade_in, float fade_out, float hold);
  void update(float dt);
  void draw(sf::RenderWindow& window);

  void startFeedback(sf::Color& colour);

  bool isFeedbackFinished() { return feedback_finished; }

private:
  void fade(float t);

// Vars
public:
private:
  sf::Texture feedback_texture;
  sf::Sprite feedback_sprite;

  FadeState fade_state = FadeState::NONE;

  float fade_in_time;
  float fade_out_time;
  float hold_time;
  float timer = 0.0f;

  sf::Color fade_colour;

  bool feedback_finished = false;

};



#endif //FEEDBACKFADE_H
