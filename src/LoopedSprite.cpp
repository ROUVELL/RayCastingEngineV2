#include <iostream>

#include "LoopedSprite.h"

LoopedSprite::LoopedSprite(Player* player, Level* level,std::string& dirName,
						   uint count, uint animTime)
	: SpriteObject(player, level), animTime(animTime)
{
	for (uint i = 0; i < count; i++)
	{
		sf::Texture frame;
		frame.loadFromFile(Settings::LOOPED_SPRITES_DIR + dirName + "\\" + std::to_string(i) + ".png");
		animation.push_back(frame);
	}

	SetTexture(&animation.front());
}

void LoopedSprite::Update()
{
	if ((uint)animClock.getElapsedTime().asMilliseconds() > animTime)
	{
		if (++currNum >= animation.size())
			currNum = 0;

		SetTexture(&animation.at(currNum));

		animClock.restart();
	}
}
