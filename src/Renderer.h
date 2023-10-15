#pragma once

#include "SpriteHandler.h"
#include "RayCasting.h"

static bool DepthComparison(const RenderData& left, const RenderData& right);

class Renderer
{
public:
	bool drawMiniMap;

	Renderer(sf::RenderWindow* window,
			 Player* player, Level* level,
			 SpriteHandler* spriteHandler,
			 RayCasting* rayCaster);

	//void ClearRenderList() { toRender.clear(); }

	void Update(float dt);
	void DrawAll() const;

private:
	sf::RenderWindow* window;
	Player* player;
	Level* level;
	SpriteHandler* spriteHandler;
	RayCasting* rayCaster;

	std::vector<RenderData> toRender;

	float skyOffset;
	sf::Texture skyTex;
	sf::Sprite sky1;
	sf::Sprite sky2;
	sf::Text debugText;
	sf::Font debugFont;

	inline void GetObjectsToRender();
	inline void UpdateDebugText(float dt);
};

