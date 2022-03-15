#ifndef GAME_ON_SFML_SOURCES_WATER_SLIME_H_
#define GAME_ON_SFML_SOURCES_WATER_SLIME_H_

#include "entity.h"
#include "cmath"
#include "player.h"
#include "SFML/Graphics.hpp"

class WaterSlime : public Entity {
 public:
  int health_;
  float target_x_, target_y_;

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
    target_x_ = 0;
    target_y_ = 0;
    is_attacking_ = false;
    GenerateFrames();
    graphics_.state_ = 2;
    graphics_.sprite_.setTextureRect(graphics_.frames_[2][0]);
  }

  void Update(float time) {
    MoveToTarget();
    graphics_.ChangeFrame(time);
  }

  void SetTarget(const Entity& target) {
    target_x_ = target.x_;
    target_y_ = target.y_;
  }

 private:
  bool is_attacking_;
  void GenerateFrames() {
    for (int j = 0; j < 5; ++j) {
      graphics_.inverse_frames_.emplace_back(0);
      for (int i = 0; i < 10; ++i) {
        graphics_.inverse_frames_[j].push_back(sf::IntRect(10 + i * 32, 172 + j * 32, 12, 20));
      }
    }
    for (int j = 0; j < 5; ++j) {
      graphics_.frames_.emplace_back(0);
      for (int i = 0; i < 10; ++i) {
        graphics_.frames_[j].push_back(sf::IntRect(10 + i * 32 + 12, 172 + j * 32, -12, 20));
      }
    }
  }

  void MoveToTarget() {
    if (target_x_ < x_) {
      graphics_.is_inverse_ = true;
    } else {
      graphics_.is_inverse_ = false;
    }
    float s = sqrt((target_y_ - y_) * (target_y_ - y_) + (target_x_ - x_) * (target_x_ - x_));
    if (s < 50) {
      if (is_attacking_) {
        return;
      }
      graphics_.current_frame_ = 0;
      graphics_.state_ = 3;
      is_attacking_ = true;
      return;
    }
    is_attacking_ = false;
    graphics_.state_ = 2;
    float cos_alpha = (target_x_ - x_) / s;
    float sin_alpha = (target_y_ - y_) / s;

    float dx_ = speed_ * cos_alpha;
    float dy_ = speed_ * sin_alpha;

    x_ += dx_;
    y_ += dy_;
  }

};

#endif //GAME_ON_SFML_SOURCES_WATER_SLIME_H_
