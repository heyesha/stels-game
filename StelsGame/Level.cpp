#include "Level.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Level::Level()
{
    // Дефолтные значения, чтобы игра не упала, если файл не загрузится
    playerStartPos = { 50.f, 50.f };
}

bool Level::loadFromFile(string& filename) 
{
    // Очищаем старые данные
    walls.clear();
    enemyConfigs.clear();

    // Открываем поток чтения файла, если открыть не получилось - выводим ошибку
    ifstream file(filename);
    if (!file.is_open()) 
    {
        cerr << "Failed to open level: " << filename << endl;
        return false;
    }

    // Построчно считываем строку из файла
    string line;
    while (getline(file, line)) 
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);
        string type;
        ss >> type;

        if (type == "PLAYER") {
            float x, y;
            ss >> x >> y;
            playerStartPos = { x, y };
        }
        else if (type == "GOAL") {
            float x, y, w, h;
            ss >> x >> y >> w >> h;
            goal.setSize({ w, h });
            goal.setPosition({ x, y });
            goal.setFillColor(sf::Color::Blue);
        }
        else if (type == "WALL") {
            float x, y, w, h;
            ss >> x >> y >> w >> h;
            sf::RectangleShape wall({ w, h });
            wall.setPosition({ x, y });
            wall.setFillColor(sf::Color(80, 80, 80));
            walls.push_back(wall);
        }
        else if (type == "ENEMY") {
            EnemyConfig config;
            float px, py;
            // Читаем пары координат до конца строки
            while (ss >> px >> py) {
                config.path.push_back({ px, py });
            }
            if (!config.path.empty()) {
                enemyConfigs.push_back(config);
            }
        }
    }
    return true;
}

/// <summary>
/// Рендерит стены на окне
/// </summary>
/// <param name="window"></param>
void Level::draw(sf::RenderWindow& window) 
{
    window.draw(goal);
    for (auto& wall : walls)
    {
        window.draw(wall);
    }
}

/// <summary>
/// Проверяет коллизию bounds со всеми стенами
/// </summary>
/// <param name="bounds"></param>
/// <returns></returns>
bool Level::checkCollision(sf::FloatRect bounds) 
{
    for (auto& wall : walls) {
        if (bounds.findIntersection(wall.getGlobalBounds()))
        {
            return true;
        }
    }
    return false;
}