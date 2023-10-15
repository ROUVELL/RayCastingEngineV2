#pragma once

#include "SpriteObject.h"

class StaticSprite
	: public SpriteObject
{
public:
	StaticSprite(Player* player,
				 Level* level,
				 std::string filename);
	~StaticSprite();
	void Update() override {};
};

