#ifndef GAMEPROJECTTP_SOURCES_PLAYER_H_
#define GAMEPROJECTTP_SOURCES_PLAYER_H_

#include "SFML/Graphics.hpp"
#include "cmath"
#include "unit.h"
#include "entity.h"

class Player : public Unit {
 public:
  std::vector<float> line_of_sight_;

  Player(float x, float y, float h, float w, float speed) : Unit() {
    is_attacking_ = false;
    is_dead_ = false;
    is_full_dead_ = false;
    health_ = 10;
    damage_ = 10;
    x_ = x;
    y_ = y;
    h_ = h;
    w_ = w;
    speed_ = speed;
    line_of_sight_ = {1, 0};
    GenerateFrames();
    graphics_.sprite_.setTextureRect(graphics_.frames_[0][0]);
  }

  void Attack(Unit *enemy) {
    std::vector<float> radius_vector(2);
    radius_vector[0] = enemy->x_ - x_;
    radius_vector[1] = enemy->y_ - y_;
    float distance = sqrt((enemy->x_ - x_) * (enemy->x_ - x_) + (enemy->y_ - y_) * (enemy->y_ - y_));
    float line_of_sight_s = sqrt(line_of_sight_[0] * line_of_sight_[0] + line_of_sight_[1] * line_of_sight_[1]);
    float angle =
        (line_of_sight_[0] * radius_vector[0] + line_of_sight_[1] * radius_vector[1]) / (distance * line_of_sight_s);
    if (is_attacking_ && static_cast<int>(graphics_.current_frame_) == 9 && angle >= 0
        && distance <= 50) {
      enemy->health_ -= damage_;
    }
  }

  void Update(float time) override {
    if (health_ <= 0) {
      Die();
    }
    KeyboardRead();
    if (!is_full_dead_) {
      graphics_.ChangeFrame(time);
    }
  }

  ~Player() {

  }

 private:
  bool is_attacking_;
  int damage_;

  void KeyboardRead() {
    if (!is_dead_) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !is_attacking_) {
        line_of_sight_ = {0, -1};
        graphics_.fps_ = 5;
        y_ -= speed_;
        graphics_.state_ = 7;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !is_attacking_) {
        line_of_sight_ = {0, 1};
        graphics_.fps_ = 5;
        y_ += speed_;
        graphics_.state_ = 7;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !is_attacking_) {
        line_of_sight_ = {1, 0};
        graphics_.fps_ = 5;
        x_ += speed_;
        graphics_.state_ = 7;
        graphics_.is_inverse_ = false;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !is_attacking_) {
        line_of_sight_ = {-1, 0};
        graphics_.fps_ = 5;
        x_ -= speed_;
        graphics_.state_ = 7;
        graphics_.is_inverse_ = true;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        graphics_.fps_ = 12;
        graphics_.state_ = 8;
        is_attacking_ = true;
      }
      if (!IsKeyPressed() || (IsKeyPressed() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && is_attacking_)) {
        graphics_.fps_ = 5;
        graphics_.state_ = 0;
        is_attacking_ = false;
      }
    }
  }

  void GenerateFrames() {
    graphics_ = Graphics("../sources/rogue.png");
    graphics_.sprite_.setTexture(graphics_.texture_);
    graphics_.sprite_.setScale(3, 3);
    for (int j = 0; j < 10; ++j) {
      graphics_.frames_.emplace_back(0);
      for (int i = 0; i < 10; ++i) {
        graphics_.frames_[j].push_back(sf::IntRect(9 + i * 32, 1 + j * 32, 20, 31));
      }
    }
    for (int j = 0; j < 10; ++j) {
      graphics_.inverse_frames_.emplace_back(0);
      for (int i = 0; i < 10; ++i) {
        graphics_.inverse_frames_[j].push_back(sf::IntRect(9 + i * 32 + 20, 1 + j * 32, -20, 31));
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
    graphics_.state_ = 9;
  }

  static bool IsKeyPressed() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
  }
};

#endif //GAMEPROJECTTP_SOURCES_PLAYER_H_
