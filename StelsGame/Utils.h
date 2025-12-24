#pragma once

const float PLAYER_SPEED = 200.f;


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
};

