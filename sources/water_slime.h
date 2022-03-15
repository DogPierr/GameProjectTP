#ifndef GAME_ON_SFML_SOURCES_WATER_SLIME_H_
#define GAME_ON_SFML_SOURCES_WATER_SLIME_H_

#include "entity.h"
#include "SFML/Graphics.hpp"

class WaterSlime : public Entity {
 public:
  int health_;
  WaterSlime(float x, float y, float h, float w, float speed) : Entity() {
    graphics_ = Graphics("../sources/water_slime.png");
    graphics_.sprite_.setTexture(graphics_.texture_);
    graphics_.sprite_.setScale(3, 3);
    health_ = 100;
    x_ = x;
    y_ = y;
    h_ = h;
    w_ = w;
    speed_ = speed;
    GenerateFrames();
    graphics_.sprite_.setTextureRect(graphics_.frames_[0][0]);
  }
 private:

  void GenerateFrames() {
    for (int j = 0; j < 10; ++j) {
      graphics_.frames_.emplace_back(0);
      for (int i = 0; i < 10; ++i) {
        graphics_.frames_[j].push_back(sf::IntRect(9 + i * 32, 1 + j * 32, 14, 31));
      }
    }
    for (int j = 0; j < 10; ++j) {
      graphics_.inverse_frames_.emplace_back(0);
      for (int i = 0; i < 10; ++i) {
        graphics_.inverse_frames_[j].push_back(sf::IntRect(9 + i * 32 + 14, 1 + j * 32, -14, 31));
      }
    }
  }
};

#endif //GAME_ON_SFML_SOURCES_WATER_SLIME_H_
