#pragma once

#include "SpriteObject.h"

class SpriteHandler
{
public:
	SpriteHandler(Player* player, Level* level);
	~SpriteHandler();

	std::vector<RenderData>& GetRenderData() { return spritesRenderData; }

	void Update();
	void Draw(sf::RenderTarget& target) const;

private:
	Player* player;
	Level* level;

	std::vector<SpriteObject*> sprites;
	std::vector<RenderData> spritesRenderData;
};

