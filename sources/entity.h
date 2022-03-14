#ifndef GAMEPROJECTTP_SOURCES_ENTITY_H_
#define GAMEPROJECTTP_SOURCES_ENTITY_H_

#include "graphics.h"
#include "SFML/Graphics.hpp"

class Entity {
 public:
  float x_, y_, speed_, h_, w_;
  Graphics graphics_;

  Entity() = default;

  Entity(Graphics &graphics, float x, float y, float h, float w, float speed)
      : graphics_(graphics), x_(x), y_(y), h_(h), w_(w), speed_(speed) {}

  void Draw(sf::RenderWindow &window) {
    graphics_.Draw(window, x_, y_);
  };

  virtual void Update() = 0;

};

#endif //GAMEPROJECTTP_SOURCES_ENTITY_H_
