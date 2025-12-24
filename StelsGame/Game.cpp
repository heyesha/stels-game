#include "Game.h"
#include <iostream>

Game::Game() : window(sf::VideoMode({ 800, 600 }), "Stealth Game Files"), isGameOver(false), isWin(false), currentLevelIndex(1)
{
    window.setFramerateLimit(60);
    loadLevel(currentLevelIndex);
}

void Game::loadLevel(int index) 
{
    // Формируем имя файла: level1.txt
    std::string filename = "level" + std::to_string(index) + ".txt";

    if (!level.loadFromFile(filename)) 
    {
        std::cerr << "Error loading level, fallback to default logic or exit" << std::endl;
    }

    // Сбрасываем игрока в новую позицию из файла
    player.shape.setPosition(level.playerStartPos);
    player.shape.setFillColor(sf::Color::Green);
    player.reset();

    // Создаем врагов на основе данных из файла
    enemies.clear();
    for (const auto& config : level.enemyConfigs) 
    {
        enemies.emplace_back(config.path);
    }

    isGameOver = false;
    isWin = false;
    std::cout << "Loaded Level " << index << std::endl;
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
void Game::processEvents() {
    while (const std::optional event = window.pollEvent()) 
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        if (const auto* key = event->getIf<sf::Event::KeyPressed>()) 
        {
            if (key->code == sf::Keyboard::Key::R) 
            {
                loadLevel(currentLevelIndex);
            }

            // Пропуск уровня
            if (key->code == sf::Keyboard::Key::N) 
            {
                currentLevelIndex++;
                if (currentLevelIndex > MAX_LEVELS) currentLevelIndex = 1;
                loadLevel(currentLevelIndex);
            }
        }

        if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) 
        {
            if (mouse->button == sf::Mouse::Button::Left) {
                std::cout << "Mouse: " << mouse->position.x << " " << mouse->position.y << std::endl;
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
    if (isGameOver)
    {
        return;
    }

    if (isWin) 
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) 
        {
            currentLevelIndex++;
            if (currentLevelIndex > MAX_LEVELS)
            {
                currentLevelIndex = 1;
                // Либо можно выйти из игры
            }
            loadLevel(currentLevelIndex);
        }
        return;
    }

    player.update(dt, level);

    // Проверка победы
    if (player.shape.getGlobalBounds().findIntersection(level.goal.getGlobalBounds())) 
    {
        isWin = true;
        player.shape.setFillColor(sf::Color::Cyan);
        std::cout << "LEVEL COMPLETE! Press SPACE for next level." << std::endl;
    }

    // Враги
    for (auto& enemy : enemies) {
        enemy.update(dt);
        enemy.checkVision(player.shape.getPosition(), level.walls);

        if (enemy.seesPlayer) {
            isGameOver = true;
            player.shape.setFillColor(sf::Color::Red);
            std::cout << "CAUGHT! Press R to restart." << std::endl;
        }
    }
}

void Game::render() {
    window.clear(sf::Color(30, 30, 30));

    level.draw(window);

    for (auto& enemy : enemies)
    {
        enemy.draw(window);
        if (enemy.seesPlayer) 
        {
            sf::Vertex line[] = 
            {
                sf::Vertex{enemy.shape.getPosition(), sf::Color::Red},
                sf::Vertex{player.shape.getPosition(), sf::Color::Red}
            };
            window.draw(line, 2, sf::PrimitiveType::Lines);
        }
    }

    player.draw(window);
    window.display();
}