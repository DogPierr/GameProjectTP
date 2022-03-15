#ifndef GAMEPROJECTTP_SOURCES_GRAPHICS_H_
#define GAMEPROJECTTP_SOURCES_GRAPHICS_H_

#include "SFML/Graphics.hpp"
#include "entity.h"

class Graphics {
 public:
  sf::Texture texture_;
  std::vector<std::vector<sf::IntRect>> frames_, inverse_frames_;
  bool is_inverse_;
  sf::Sprite sprite_;
  float fps_, current_frame_, state_;

  Graphics() : frames_(0), inverse_frames_(0), is_inverse_(false), fps_(5), current_frame_(0), state_(0) {}

  Graphics(const std::string &image)
      : frames_(0), inverse_frames_(0), is_inverse_(false), fps_(5), current_frame_(0), state_(0) {
    texture_.loadFromFile(image);
  }

  void Draw(sf::RenderWindow &window, float x, float y) {
    sprite_.setPosition(x, y);
    window.draw(sprite_);
  }

  void ChangeFrame(float time) {
    current_frame_ += fps_ * time;
    if (current_frame_ > frames_[state_].size()) {
      current_frame_ -= frames_[state_].size();
    }
    if (!is_inverse_) {
      sprite_.setTextureRect(frames_[state_][current_frame_]);
      return;
    }
    sprite_.setTextureRect(inverse_frames_[state_][current_frame_]);
  }

};

#endif //GAMEPROJECTTP_SOURCES_GRAPHICS_H_
