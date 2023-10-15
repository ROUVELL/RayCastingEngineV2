#pragma once

#include "StaticSprite.h"

class SpriteHandler
{
public:
	SpriteHandler(Player* player, Level* level);
	~SpriteHandler();

	std::vector<RenderData>& GetRenderData() { return spritesRenderData; }

	void CreateSprite(sf::Vector2f& position, std::string& filename,
					  float shift = 0.27f, float scale = 1.f);
	void CreateLooped(sf::Vector2f& position, std::string& dirName,
					  uint count, uint animTime,
					  float shift = 0.13f, float scale = 1.f);

	void Update();
	void Draw(sf::RenderTarget& target) const;

private:
	Player* player;
	Level* level;

	std::vector<SpriteObject*> sprites;
	std::vector<RenderData> spritesRenderData;
};

