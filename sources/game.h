
#ifndef GAME_ON_SFML_SOURCES_GAME_H_
#define GAME_ON_SFML_SOURCES_GAME_H_

#include "SFML/Graphics.hpp"
#include "entity.h"
#include "graphics.h"
#include "player.h"

class GameLoop {
 public:
  GameLoop() : window(sf::VideoMode(800, 800), "plswork"),
               graphics(Graphics()),
               player(graphics, 0, 0, 10, 10, 0.1) {}

  void Run() {
    while (window.isOpen()) {
      sf::Event event;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          window.close();
        }
      }
      player.Update();
      window.clear();
      player.Draw(window);
      window.display();
    }
  }

  void Terminate() {}

 private:
  sf::RenderWindow window;
  Graphics graphics;
  Player player;
};


#endif //GAME_ON_SFML_SOURCES_GAME_H_