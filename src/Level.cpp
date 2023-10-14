#include <vector>
#include <fstream>
#include <iostream>

#include "Level.h"


Level::Level() : width(0), height(0), offsetY(0)
{
}

void Level::LoadFromFile(const std::string& filename)
{
	std::ifstream levelFile(Settings::LEVELS_DIR + filename);

	std::string line;

	levelFile >> width >> height;

	// переходимо на наступний радок
	levelFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
	char texNum;
	uint rowNum = 0;
	map.push_back(std::vector<uint>{});
	while (levelFile.get(texNum))
	{
		if (texNum == '\n')
		{
			++rowNum;
			map.push_back(std::vector<uint>{});
			continue;
		}
		
		if (texNum == '.')
			map.at(rowNum).push_back(0);
		else
			map.at(rowNum).push_back(texNum - '0');
	}

	offsetY = Settings::SCREEN_HEIGHT - height * Settings::TILE_SIZE;
}

uint Level::Get(int x, int y) const
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return 0;

	return map[y][x];
}

void Level::Draw(sf::RenderTarget& target) const
{
	sf::RectangleShape tile(sf::Vector2f((float)Settings::TILE_SIZE, (float)Settings::TILE_SIZE));
	tile.setFillColor(sf::Color::Transparent);
	tile.setOutlineColor(sf::Color(170, 170, 170, 200));
	tile.setOutlineThickness(-1.f);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (map[y][x] != 0)
			{
				tile.setPosition(x * Settings::TILE_SIZE, offsetY + y * Settings::TILE_SIZE);

				target.draw(tile);
			}
		}
	}
}
