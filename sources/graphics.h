#ifndef GAMEPROJECTTP_SOURCES_GRAPHICS_H_
#define GAMEPROJECTTP_SOURCES_GRAPHICS_H_

#include "SFML/Graphics.hpp"
#include "entity.h"

class Graphics {
 public:
  std::vector<sf::IntRect> frames_;
  sf::Sprite sprite_;
  float fps_, current_frame_;

  Graphics() : frames_(0), fps_(0), current_frame_(0) {}


  void Draw(sf::RenderWindow& window, float x, float y) {
    sprite_.setPosition(x, y);
    window.draw(sprite_);
  }

  void ChangeFrame(float time) {
    current_frame_ += fps_ * time;
    if (current_frame_ > frames_.size()) {
      current_frame_ -= frames_.size();
    }
    sprite_.setTextureRect(frames_[current_frame_]);
  }

};

#endif //GAMEPROJECTTP_SOURCES_GRAPHICS_H_
