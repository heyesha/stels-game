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

	static float cross2(sf::Vector2f a, sf::Vector2f b)
	{
		return a.x * b.y - a.y * b.x;
	}

	static bool checkIntersection(sf::Vector2f a1, sf::Vector2f a2,
		sf::Vector2f b1, sf::Vector2f b2)
	{
		const float EPS = 1e-5f;

		sf::Vector2f aDir = a2 - a1;
		sf::Vector2f bDir = b2 - b1;

		float det = cross2(aDir, bDir);
		if (std::abs(det) < EPS)
			return false;

		sf::Vector2f aToB = b1 - a1;

		float t = cross2(aToB, bDir) / det;
		float u = cross2(aToB, aDir) / det;

		if (t < 0.f || t > 1.f) return false;
		if (u < 0.f || u > 1.f) return false;

		return true;
	}
};

