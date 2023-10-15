#pragma once

#include "SpriteObject.h"

class LoopedSprite :
    public SpriteObject
{
public:
	LoopedSprite(Player* player,
				 Level* level,
				 std::string& dirName,
				 uint count,
				 uint animTime);

	void Update() override;

private:
	std::vector<sf::Texture> animation;
	sf::Clock animClock;
	uint animTime;
	uint currNum = 0;
};

