#pragma once

#include "Settings.h"

class Level
{
public:
	Level();


	bool IsEmpty(int x, int y) const { return Get(x, y) == 0; }
	uint Get(int x, int y) const;
	int GetOffsetY() const { return offsetY; }
	sf::Vector2u GetSize() const { return sf::Vector2u{width, height}; }

	void LoadFromFile(const std::string& filename);
	void Draw(sf::RenderTarget& target) const;

private:
	std::vector<std::vector<uint>> map;

	uint width;
	uint height;
	int offsetY;
};