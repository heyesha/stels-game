#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include "Level.h"
#include "Player.h"
#include "Enemy.h"

class Game
{
public:
	Game();
	void run();

private:
    void processEvents();
    void update(float dt);
    void render();
    void initEnemies();

    sf::RenderWindow window;
    Level level;
    Player player;
    std::vector<Enemy> enemies;

    bool isGameOver;
    bool isWin;
};

