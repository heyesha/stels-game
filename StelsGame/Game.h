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

    void loadLevel(int index);
    void initUI();

    sf::Font font;
    sf::Text statusText;
    sf::Text infoText;

    sf::RenderWindow window;
    Level level;
    Player player;
    std::vector<Enemy> enemies;

    bool isGameOver;
    bool isWin;

    int currentLevelIndex;
    const int MAX_LEVELS = 4;
};

