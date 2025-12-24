#pragma once

const float PLAYER_SPEED = 200.f;
const float ENEMY_SPEED = 100.f;
const float VIEW_DISTANCE = 300.f;
const float VIEW_ANGLE = 45.f;
const float DEG_TO_RAD = 3.14159f / 180.f;

class Geometry
{
public:
	/// <summary>
	/// Считает длину вектора v
	/// </summary>
	/// <param name="v"></param>
	/// <returns></returns>
	static float getLength(sf::Vector2f v)
	{
		return std::sqrt(v.x * v.x + v.y * v.y);
	}

	/// <summary>
	/// Нормализует вектор v
	/// </summary>
	/// <param name="v"></param>
	/// <returns></returns>
	static sf::Vector2f normalize(sf::Vector2f v)
	{
		float len = getLength(v);
		
		if (len != 0)
		{
			return v / len;
		}
		else
		{
			return v;
		}
	}

	static bool checkIntersection(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f p4) {
		auto cross = [](sf::Vector2f a, sf::Vector2f b) { return a.x * b.y - a.y * b.x; };
		sf::Vector2f r = p2 - p1;
		sf::Vector2f s = p4 - p3;
		float rxs = cross(r, s);
		if (std::abs(rxs) < 1e-5f) return false;
		sf::Vector2f qp = p3 - p1;
		float t = cross(qp, s) / rxs;
		float u = cross(qp, r) / rxs;
		return (t >= 0 && t <= 1 && u >= 0 && u <= 1);
	}
};

