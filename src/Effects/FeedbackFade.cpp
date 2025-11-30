//
// Created by Harry Skerritt on 30/11/2025.
//

#include "FeedbackFade.h"

#include <iostream>

FeedbackFade::FeedbackFade() {  }


void FeedbackFade::init(std::string texture_loc, float fade_in, float fade_out, float hold)
{
  if (!feedback_texture.loadFromFile(texture_loc)) {
    std::cerr << "FeedbackFade: Error loading texture" << std::endl;
  }
  feedback_sprite.setTexture(feedback_texture);
  feedback_sprite.setScale(0.5f, 0.5f);

  sf::Color col = fade_colour;
  col.a = 0;
  feedback_sprite.setColor(col);

  fade_in_time = fade_in;
  fade_out_time = fade_out;
  hold_time = hold;
}

void FeedbackFade::update(float dt)
{
    timer += dt;

    switch (fade_state)
    {
      case FadeState::NONE:
        break;

      case FadeState::FADE_IN:
        if (timer >= fade_in_time)
        {
          feedback_sprite.setColor(fade_colour);
          timer = 0.0f;
          fade_state = FadeState::HOLD;
        }
        else
        {
            float t = timer / fade_in_time;
            fade(t);
        }
        break;

      case FadeState::HOLD:
        if (timer >= hold_time)
        {
          timer = 0.0f;
          fade_state = FadeState::FADE_OUT;
        }
        break;

    case FadeState::FADE_OUT:
        if (timer >= fade_out_time)
        {
          timer = 0.0f;
          fade_state = FadeState::NONE;
        }
        else
        {
          float t = 1.0f - (timer / fade_out_time);
          fade(t);
        }
        break;

    }
}

void FeedbackFade::draw(sf::RenderWindow& window) {
  window.draw(feedback_sprite);
}

void FeedbackFade::startFeedback(sf::Color &colour) {
  fade_colour = colour;
  fade_state = FadeState::FADE_IN;
  timer = 0.0f;

  sf::Color col = fade_colour;
  col.a = 0;
  feedback_sprite.setColor(col);
}



// --- PRIVATE ---
void FeedbackFade::fade(float t) {
  sf::Color colour = fade_colour;
  colour.a = static_cast<sf::Uint8>(255 * t);
  feedback_sprite.setColor(colour);
}

