#include <cmath>

#include "Game.h"

Game::Game() : dt(0.1f), skyOffset(0.f), drawMiniMap(false),
				player(&level), rayCaster(&window, &player, &level)
{
	// sky texture settings
	skyTex.loadFromFile(Settings::TEXTURES_DIR + "sky.png");
	sf::Vector2u skyRect = skyTex.getSize();
	sf::Vector2f scale((float)Settings::SCREEN_WIDTH / skyRect.x,
					   (float)Settings::H_SCREEN_HEIGHT / skyRect.y);

	sky1.setTexture(skyTex);
	sky1.setScale(scale);
	sky2.setTexture(skyTex);
	sky2.setScale(scale);

	debugFont.loadFromFile(Settings::FONTS_DIR + "Comfortaa-Regular.ttf");
	debugText.setCharacterSize(20);
	debugText.setFillColor(sf::Color::White);
	debugText.setFont(debugFont);

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
				drawMiniMap = !drawMiniMap;
			break;
		

		default:
			break;
		}
	}
}

void Game::Update()
{
	player.Update(dt);
	rayCaster.Update();

	skyOffset = std::fmodf(skyOffset + Settings::SCREEN_WIDTH + 4.f * player.GetRel(), (float)Settings::SCREEN_WIDTH);
	sky1.setPosition(-skyOffset, 0.f);
	sky2.setPosition(-skyOffset + Settings::SCREEN_WIDTH, 0.f);
	
	std::string FPS = std::to_string((int)(1.f / dt));
	std::string X = "\n\nX: " + std::to_string(player.GetPosition().x);
	std::string Y = "  Y: " + std::to_string(player.GetPosition().y);
	std::string angle = "\nAngle: " + std::to_string(player.GetAngle() * 180.f / Settings::PI);

	debugText.setString(FPS + X + Y + angle);
}

void Game::Draw()
{
	window.clear();

	window.draw(sky1);
	window.draw(sky2);

	rayCaster.Draw3D();

	if (drawMiniMap)
	{
		level.Draw(window);
		rayCaster.Draw2D();
		player.Draw(window);
	}
	
	window.draw(debugText);

	window.display();
}
