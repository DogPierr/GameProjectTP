#ifndef GAME_ON_SFML_SOURCES_GAME_H_
#define GAME_ON_SFML_SOURCES_GAME_H_

#include "SFML/Graphics.hpp"
#include "entity.h"
#include "dynamic_graphics.h"
#include "map.h"
#include "player.h"
#include "water_slime.h"

class GameLoop {
 public:
  GameLoop()
      : window(sf::VideoMode(1000, 1000), "plswork"),
        graphics(DynamicGraphics()),
        player(new Player(0, 0, 10, 10, 0.1)),
        fire_(new Fire),
        water_slimes_() {}

  void Run() {
    sf::View camera;
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
      window.clear();
      fire_->DrawBackground(window);
      for (auto slime : water_slimes_) {
        slime->SetTarget(player);
        slime->Update(time);
        slime->Draw(window);
        player->Attack(slime);
      }
      player->Update(time);
      player->Draw(window);
      for (auto slime : water_slimes_) {
        slime->Draw(window);
      }
      fire_->DrawFrame(window);
      if (!fire_->IsInRadius(player)) {
        player->DrawBackground(window);
        for (auto slime : water_slimes_) {
          slime->SetTarget(player);
          slime->Update(time);
          slime->Draw(window);
          player->Attack(slime);
        }
        player->DrawFrame(window);
        player->Draw(window);
      }
      fire_->Update(time);
      fire_->Draw(window);
      camera.setCenter(player->x_, player->y_);
      window.setView(camera);
      window.display();
    }
  }

  void Terminate() {}

 private:
  sf::RenderWindow window;
  std::vector<WaterSlime*> water_slimes_;
  DynamicGraphics graphics;
  Player* player;
  Fire* fire_;
};

#endif  // GAME_ON_SFML_SOURCES_GAME_H_