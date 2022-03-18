#ifndef GAME_ON_SFML_SOURCES_WATER_SLIME_H_
#define GAME_ON_SFML_SOURCES_WATER_SLIME_H_

#include "entity.h"
#include "cmath"
#include "player.h"
#include "SFML/Graphics.hpp"

class WaterSlime : public Unit {
 public:
  WaterSlime(float x, float y, float h, float w, float speed) : Unit() {
    health_ = 10;
    damage_ = 5;
    x_ = x;
    y_ = y;
    h_ = h;
    w_ = w;
    speed_ = speed;
    is_attacking_ = false;
    GenerateFrames();
    graphics_.state_ = 2;
    graphics_.sprite_.setTextureRect(graphics_.frames_[2][0]);
    graphics_.sprite_.setColor(sf::Color(255, 255, 255, 50));
  }

  void Update(float time) {
    if (health_ <= 0) {
      Die();
    } else {
      if (target_ != NULL) {
        MoveToTarget();
      }
      if (target_->health_ <= 0) {
        target_ = NULL;
      }
    }
    if (!is_full_dead_) {
      graphics_.ChangeFrame(time);
    }
  }

  void SetTarget(Mortal* target) {
    target_ = target;
  }

 private:
  bool is_attacking_;
  int damage_;
  Mortal* target_;

  void GenerateFrames() {
    graphics_ = Graphics("../sources/water_slime.png");
    graphics_.sprite_.setTexture(graphics_.texture_);
    graphics_.sprite_.setScale(3, 3);
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

  void Die() {
    speed_ = 0;
    if (!is_dead_) {
      graphics_.current_frame_ = 0;
      is_dead_ = true;
    }
    if (static_cast<int>(graphics_.current_frame_) == 9) {
      is_full_dead_ = true;
    }
    graphics_.state_ = 4;
  }

  void MoveToTarget() {
    if (target_->x_ < x_) {
      graphics_.is_inverse_ = true;
    } else {
      graphics_.is_inverse_ = false;
    }
    float s = sqrt((target_->y_ - y_) * (target_->y_ - y_) + (target_->x_ - x_) * (target_->x_ - x_));
    if (s < 50) {
      Attack();
      return;
    }
    is_attacking_ = false;
    graphics_.state_ = 2;
    float cos_alpha = (target_->x_ - x_) / s;
    float sin_alpha = (target_->y_ - y_) / s;

    float dx_ = speed_ * cos_alpha;
    float dy_ = speed_ * sin_alpha;

    x_ += dx_;
    y_ += dy_;
  }

  void Attack() {
    if (is_attacking_) {
      if (static_cast<int>(graphics_.current_frame_) == 9) {
        target_->health_ -= damage_;
        graphics_.current_frame_ = 0;
      }
      return;
    }
    graphics_.fps_ = 15;
    graphics_.current_frame_ = 0;
    graphics_.state_ = 3;
    is_attacking_ = true;
  }

};

#endif //GAME_ON_SFML_SOURCES_WATER_SLIME_H_
