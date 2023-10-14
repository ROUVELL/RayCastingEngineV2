#pragma once

#include "RayCasting.h"

class Game
{
public:
	Game();

	void Run();

private:
	sf::RenderWindow window;
	float dt;

	Level level;
	Player player;
	RayCasting rayCaster;

	float skyOffset;
	sf::Texture skyTex;
	sf::Sprite sky1;
	sf::Sprite sky2;
	sf::Text debugText;
	sf::Font debugFont;

	bool drawMiniMap;

	void ProcessEvents();
	void Update();
	void Draw();
};