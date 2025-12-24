#include "Game.h"
#include <iostream>

Game::Game() : window(sf::VideoMode({ 800, 600 }), "Stealth Game Files"), isGameOver(false), isWin(false)
{
    window.setFramerateLimit(60);
    initEnemies();
}

/// <summary>
/// Инициализация противников
/// </summary>
void Game::initEnemies() 
{
    enemies.clear();
    enemies.emplace_back(std::vector<sf::Vector2f>{{300, 100}, { 700, 100 }});
    enemies.emplace_back(std::vector<sf::Vector2f>{{400, 500}, { 600, 300 }, { 200, 300 }});
}

/// <summary>
/// Процесс игры
/// </summary>
void Game::run() 
{
    sf::Clock clock;
    while (window.isOpen()) 
    {
        float dt = clock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }
}

/// <summary>
/// Обработка игровых событий
/// </summary>
void Game::processEvents() 
{
    while (const std::optional event = window.pollEvent()) 
    {
        if (event->is<sf::Event::Closed>()) window.close();

        if (const auto* key = event->getIf<sf::Event::KeyPressed>()) 
        {
            if (key->code == sf::Keyboard::Key::R) 
            {
                isGameOver = false;
                isWin = false;
                player.reset();
                initEnemies();
            }
        }
    }
}

/// <summary>
/// Обновление игры в каждом кадре
/// </summary>
/// <param name="dt"></param>
void Game::update(float dt) 
{
    if (isGameOver || isWin)
    {
        return;
    }

    player.update(dt, level);

    if (player.shape.getGlobalBounds().findIntersection(level.goal.getGlobalBounds())) {
        isWin = true;
        player.shape.setFillColor(sf::Color::Cyan);
        std::cout << "YOU WIN!" << std::endl;
    }

    for (auto& enemy : enemies) {
        enemy.update(dt);
        enemy.checkVision(player.shape.getPosition(), level.walls);

        if (enemy.seesPlayer) {
            isGameOver = true;
            player.shape.setFillColor(sf::Color::Red);
            std::cout << "CAUGHT!" << std::endl;
        }
    }
}

void Game::render() {
    window.clear(sf::Color(30, 30, 30));

    level.draw(window);

    for (auto& enemy : enemies) {
        enemy.draw(window);
        if (enemy.seesPlayer) {
            sf::Vertex line[] = {
                sf::Vertex{enemy.shape.getPosition(), sf::Color::Red},
                sf::Vertex{player.shape.getPosition(), sf::Color::Red}
            };
            window.draw(line, 2, sf::PrimitiveType::Lines);
        }
    }

    player.draw(window);
    window.display();
}