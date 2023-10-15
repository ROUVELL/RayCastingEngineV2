#include <cmath>

#include "Game.h"

Game::Game() : dt(0.1f), player(&level),
			rayCaster(&window, &player, &level),
			renderer(&window, &player, &level, &rayCaster)
{
	level.LoadFromFile("0.txt");

	if (Settings::FULLSCREEN)
		window.create(sf::VideoMode().getFullscreenModes().front(), "Ray Casting Engine", sf::Style::Fullscreen);
	else
		window.create(sf::VideoMode(Settings::SCREEN_WIDTH, Settings::SCREEN_HEIGHT), "Ray Casting Engine", sf::Style::None);

	window.setPosition(sf::Vector2i(Settings::H_MONITOR_WIDTH - Settings::H_SCREEN_WIDTH,
									Settings::H_MONITOR_HEIGHT - Settings::H_SCREEN_HEIGHT));

	window.setMouseCursorGrabbed(true);
	window.setMouseCursorVisible(false);
	window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(60);
}

void Game::Run()
{
	sf::Clock clock;
	while (window.isOpen())
	{
		dt = clock.restart().asSeconds();

		ProcessEvents();
		Update();
		Draw();
	}
}

void Game::ProcessEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				window.close();
			else if (event.key.code == sf::Keyboard::M)
				renderer.drawMiniMap = !renderer.drawMiniMap;
			break;
		

		default:
			break;
		}
	}
}

void Game::Update()
{
	renderer.ClearRenderList();

	player.Update(dt);
	rayCaster.Update();

	renderer.Update(dt);
}

void Game::Draw()
{
	window.clear();

	renderer.DrawAll();

	window.display();
}
