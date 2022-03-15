#ifndef GAMEPROJECTTP_SOURCES_PLAYER_H_
#define GAMEPROJECTTP_SOURCES_PLAYER_H_

#include "SFML/Graphics.hpp"
#include "map"
#include "entity.h"

class Player : public Entity {
 public:
  int health_;
  Player(float x, float y, float h, float w, float speed) : Entity() {
    is_attacking_ = false;
    graphics_ = Graphics("../sources/rogue.png");
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

  void Update(float time) override {
    KeyboardRead();
    graphics_.ChangeFrame(time);
  }

 private:
  bool is_attacking_;
  void KeyboardRead() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !is_attacking_) {
      graphics_.fps_ = 5;
      y_ -= speed_;
      graphics_.state_ = 7;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !is_attacking_) {
      graphics_.fps_ = 5;
      y_ += speed_;
      graphics_.state_ = 7;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !is_attacking_) {
      graphics_.fps_ = 5;
      graphics_.is_inverse_ = false;
      x_ += speed_;
      graphics_.state_ = 7;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !is_attacking_) {
      graphics_.fps_ = 5;
      graphics_.is_inverse_ = true;
      x_ -= speed_;
      graphics_.state_ = 7;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
      is_attacking_ = true;
      graphics_.fps_ = 12;
      graphics_.state_ = 8;
    }
    if (!IsKeyPressed() || (IsKeyPressed() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && is_attacking_)) {
      graphics_.fps_ = 5;
      graphics_.state_ = 0;
      is_attacking_ = false;
    }
  }

  void GenerateFrames() {
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

  void Attack() {

  }

  bool IsKeyPressed() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
  }
};

#endif //GAMEPROJECTTP_SOURCES_PLAYER_H_
