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

struct RenderData
{
	float depth;
	sf::Sprite sprite;
};

class RayCasting
{
public:
	RayCasting(Player* player, Level* level);

	std::array<RenderData, Settings::NUM_RAYS>& GetWalls();

	void Update();
	void Draw(sf::RenderTarget& target) const;

private:
	Player* player;
	Level* level;

	std::array<Ray, Settings::NUM_RAYS> raysData;
	std::array<RenderData, Settings::NUM_RAYS> walls;
	std::array<sf::Texture, Settings::TEXTURES_COUNT> textures;
};

