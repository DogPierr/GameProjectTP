#ifndef GAMEPROJECTTP_SOURCES_PLAYER_H_
#define GAMEPROJECTTP_SOURCES_PLAYER_H_

#include "iostream"
#include "SFML/Graphics.hpp"
#include "entity.h"

class Player : public Entity {
 public:
  Player(float x, float y, float h, float w, float speed) : Entity() {
    x_ = x;
    y_ = y;
    h_ = h;
    w_ = w;
    speed_ = speed;
    sf::Texture texture;
    texture.loadFromFile("/home/dogpie/Projects/GameProjectTP/pls.png");
    graphics_.sprite_.setTexture(texture);
    graphics_.frames_.push_back(sf::IntRect(10, 10, 32, 32));
  }

  void Update() override {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      y_ -= speed_;
      graphics_.sprite_.move(0, -speed_);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
      y_ += speed_;
      graphics_.sprite_.move(0, speed_);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      x_ += speed_;
      graphics_.sprite_.move(speed_, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      x_ -= speed_;
      graphics_.sprite_.move(-speed_, 0);
    }
  }

};


#endif //GAMEPROJECTTP_SOURCES_PLAYER_H_
