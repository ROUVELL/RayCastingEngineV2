#pragma once

#include "Renderer.h"

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
	SpriteHandler spriteHandler;
	Renderer renderer;

	void ProcessEvents();
	void Update();
	void Draw();
};