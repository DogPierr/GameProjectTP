#ifndef GAME_ON_SFML_SOURCES_OBJECT_H_
#define GAME_ON_SFML_SOURCES_OBJECT_H_

#include "SFML/Graphics.hpp"
#include "graphics.h"
#include "entity.h"

class Unit : public Entity {
 public:
  float speed_;
  bool is_dead_, is_full_dead_;

  Unit() = default;

  void Draw(sf::RenderWindow &window) {
    graphics_.Draw(window, x_, y_);
  };

  virtual void Update(float time) = 0;

};

#endif //GAME_ON_SFML_SOURCES_OBJECT_H_
