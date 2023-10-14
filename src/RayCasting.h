#pragma once

#include <array>

#include "Player.h"

struct Ray
{
	int rayNum;
	float depth;
	float projHeight;
	int texNum;
	float offset;
	float angle;
};

class RayCasting
{
public:
	RayCasting(sf::RenderWindow* window, Player* player, Level* level);

	void Update();
	void Draw2D();
	void Draw3D();

private:
	sf::RenderWindow* window;
	Player* player;
	Level* level;

	std::array<Ray, Settings::NUM_RAYS> raysData;
	std::array<sf::Texture, Settings::TEXTURES_COUNT> textures;
};

