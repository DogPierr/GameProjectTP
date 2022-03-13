#ifndef GAMEPROJECTTP_SOURCES_PLAYER_H_
#define GAMEPROJECTTP_SOURCES_PLAYER_H_

#include "iostream"
#include "SFML/Graphics.hpp"
#include "entity.h"

class Player : public Entity {
 public:
  Player(Graphics &graphics, float x, float y, float h, float w, float speed) : Entity(graphics, x, y, h, w, speed) {
    sf::Texture texture;
    texture.loadFromFile("/home/dogpie/Projects/GameProjectTP/pls.png");
    graphics_.sprite_.setTexture(texture);
    graphics_.frames_.emplace_back(0, 0, 32, 32);
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
