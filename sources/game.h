#ifndef GAME_ON_SFML_SOURCES_GAME_H_
#define GAME_ON_SFML_SOURCES_GAME_H_

#include "SFML/Graphics.hpp"
#include "entity.h"
#include "graphics.h"
#include "player.h"
#include "water_slime.h"

class GameLoop {
 public:
  GameLoop() : window(sf::VideoMode(800, 800), "plswork"),
               graphics(Graphics()),
               player(new Player(100, 100, 10, 10, 0.1)),
               water_slimes_() {}

  void Run() {
    sf::Clock timer;
    water_slimes_.push_back(new WaterSlime(0, 0, 10, 10, 0.05));
    water_slimes_.push_back(new WaterSlime(800, 0, 10, 10, 0.05));
    water_slimes_.push_back(new WaterSlime(0, 800, 10, 10, 0.05));
    water_slimes_.push_back(new WaterSlime(800, 800, 10, 10, 0.05));

    while (window.isOpen()) {
      float time = timer.getElapsedTime().asSeconds();
      timer.restart();

      sf::Event event;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          window.close();
        }
      }
      for (auto slime: water_slimes_) {
        slime->SetTarget(player);
        slime->Update(time);
        slime->Draw(window);
        player->Attack(slime);
      }
      player->Update(time);
      window.clear();
      player->Draw(window);
      for (auto slime : water_slimes_) {
        slime->Draw(window);
      }
      window.display();
    }
  }

  void Terminate() {}

 private:
  sf::RenderWindow window;
  std::vector<WaterSlime*> water_slimes_;
  Graphics graphics;
  Player *player;
};


#endif //GAME_ON_SFML_SOURCES_GAME_H_