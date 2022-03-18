#ifndef GAME_ON_SFML_SOURCES_MORTAL_H_
#define GAME_ON_SFML_SOURCES_MORTAL_H_

#include "SFML/Graphics.hpp"
#include "entity.h"

class Mortal : public Entity {
 public:
  int health_;

  Mortal() = default;
};

#endif //GAME_ON_SFML_SOURCES_MORTAL_H_
