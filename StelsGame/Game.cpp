#include "Game.h"
#include <iostream>

Game::Game() : window(sf::VideoMode({ 800, 600 }), "Stealth Game Files"), isGameOver(false), isWin(false), 
currentLevelIndex(1), 
statusText(font),
infoText(font)
{
    window.setFramerateLimit(60);

    initUI();
    loadLevel(currentLevelIndex);
}

/// <summary>
/// Инициализация UI
/// </summary>
void Game::initUI() {
    if (!font.openFromFile("arial.ttf")) 
    {
        std::cerr << "ERROR: Failed to load arial.ttf" << std::endl;
    }

    statusText.setFont(font);
    statusText.setCharacterSize(50);
    statusText.setFillColor(sf::Color::White);
    statusText.setString("");

    infoText.setFont(font);
    infoText.setCharacterSize(20);
    infoText.setFillColor(sf::Color::White);
    infoText.setPosition({ 10.f, 10.f });
}

/// <summary>
/// Загрузка уровня из файла по индексу
/// </summary>
/// <param name="index"></param>
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

    statusText.setString("");
    infoText.setString("Level: " + std::to_string(index));

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

    if (player.shape.getGlobalBounds().findIntersection(level.goal.getGlobalBounds())) 
    {
        isWin = true;
        player.shape.setFillColor(sf::Color::Cyan);
        std::cout << "LEVEL COMPLETE! Press SPACE for next level." << std::endl;

        statusText.setString("LEVEL COMPLETE!\nPress Space");
        statusText.setFillColor(sf::Color::Green);

        sf::FloatRect textRect = statusText.getLocalBounds();
        statusText.setOrigin({ textRect.size.x / 2.f, textRect.size.y / 2.f });
        statusText.setPosition({ 800.f / 2.f, 600.f / 2.f });
    }

    for (auto& enemy : enemies) {
        enemy.update(dt);
        enemy.checkVision(player.shape.getPosition(), level.walls);

        if (enemy.seesPlayer) {
            isGameOver = true;
            player.shape.setFillColor(sf::Color::Red);
            std::cout << "CAUGHT! Press R to restart." << std::endl;

            statusText.setString("CAUGHT!\nPress R to restart");
            statusText.setFillColor(sf::Color::Red);

            sf::FloatRect textRect = statusText.getLocalBounds();
            statusText.setOrigin({ textRect.size.x / 2.f, textRect.size.y / 2.f });
            statusText.setPosition({ 800.f / 2.f, 600.f / 2.f });
        }
    }
}

void Game::render() 
{
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

    window.draw(infoText);

    if (isGameOver || isWin) 
    {

        window.draw(statusText);
    }

    window.display();
}