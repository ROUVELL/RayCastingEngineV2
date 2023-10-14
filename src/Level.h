#pragma once


#include "Settings.h"

class Level
{
public:
	Level();

	void LoadFromFile(const std::string& filename);
	bool IsEmpty(int x, int y) const { return Get(x, y) == 0; }
	uint Get(int x, int y) const;
	void Draw(sf::RenderTarget& target) const;

private:
	std::vector<std::vector<uint>> map;

	uint width;
	uint height;
};

