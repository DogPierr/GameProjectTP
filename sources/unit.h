#ifndef GAME_ON_SFML_SOURCES_OBJECT_H_
#define GAME_ON_SFML_SOURCES_OBJECT_H_

#include "SFML/Graphics.hpp"
#include "graphics.h"
#include "mortal.h"

class Unit : public Mortal {
 public:
  float speed_;
  bool is_dead_, is_full_dead_;

  Unit() = default;

  virtual void Update(float time) = 0;

};

#endif //GAME_ON_SFML_SOURCES_OBJECT_H_
