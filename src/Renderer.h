#pragma once

#include "SFML/Graphics.hpp"
#include "Settings.h"

class Player;
class Level;
class RayCasting;

class Renderer
{
public:
	bool drawMiniMap;

	Renderer(sf::RenderWindow* window,
			 Player* player, Level* level,
			 RayCasting* rayCaster);

	void ClearRenderList() { toRender.clear(); }

	void Update(float dt);
	void DrawAll() const;

private:
	sf::RenderWindow* window;
	Player* player;
	Level* level;
	RayCasting* rayCaster;

	std::vector<int> toRender;

	float skyOffset;
	sf::Texture skyTex;
	sf::Sprite sky1;
	sf::Sprite sky2;
	sf::Text debugText;
	sf::Font debugFont;
};

