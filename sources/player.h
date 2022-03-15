#ifndef GAMEPROJECTTP_SOURCES_PLAYER_H_
#define GAMEPROJECTTP_SOURCES_PLAYER_H_

#include "iostream"
#include "SFML/Graphics.hpp"
#include "entity.h"

class Player : public Entity {
 public:
  Player(float x, float y, float h, float w, float speed) : Entity() {
    graphics_ = Graphics("../sources/rogue.png");
    graphics_.sprite_.setTexture(graphics_.texture_);
    graphics_.sprite_.setScale(3, 3);

    x_ = x;
    y_ = y;
    h_ = h;
    w_ = w;
    speed_ = speed;
    GenerateFrames();
    graphics_.sprite_.setTextureRect(graphics_.frames_[0][0]);
  }

  void Keyboard() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      graphics_.fps_ = 5;
      y_ -= speed_;
      graphics_.state_ = 7;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
      graphics_.fps_ = 5;
      y_ += speed_;
      graphics_.state_ = 7;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      graphics_.fps_ = 5;
      graphics_.is_inverse_ = false;
      x_ += speed_;
      graphics_.state_ = 7;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      graphics_.fps_ = 5;
      graphics_.is_inverse_ = true;
      x_ -= speed_;
      graphics_.state_ = 7;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
      graphics_.fps_ = 12;
      graphics_.state_ = 8;
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S)
        && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)
        && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
      graphics_.fps_ = 5;
      graphics_.state_ = 0;
    }
  }

  void Update(float time) override {
    Keyboard();
    graphics_.ChangeFrame(time);
  }

  void GenerateFrames() {
    for (int j = 0; j < 10; ++j) {
      graphics_.frames_.push_back(std::vector<sf::IntRect>(0));
      for (int i = 0; i < 10; ++i) {
        graphics_.frames_[j].push_back(sf::IntRect(9 + i * 32, 1 + j * 32, 14, 31));
      }
    }
    for (int j = 0; j < 10; ++j) {
      graphics_.inverse_frames_.push_back(std::vector<sf::IntRect>(0));
      for (int i = 0; i < 10; ++i) {
        graphics_.inverse_frames_[j].push_back(sf::IntRect(9 + i * 32 + 14, 1 + j * 32, -14, 31));
      }
    }
  }

  void Attack() {

  }

};

#endif //GAMEPROJECTTP_SOURCES_PLAYER_H_
