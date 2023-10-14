#include "Game.h"

Game::Game() : dt(0.1f), skyOffset(0.f), player(&level),
				rayCaster(&window, &player, &level)
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

	fpsFont.loadFromFile(Settings::FONTS_DIR + "Comfortaa-Regular.ttf");
	fpsText.setCharacterSize(20);
	fpsText.setFillColor(sf::Color::White);
	fpsText.setFont(fpsFont);

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
	//window.setFramerateLimit(Settings::FPS);
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

		default:
			break;
		}

		//player.ProcessEvents(event);
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
	std::string X = "\nX: " + std::to_string(player.GetPosition().x);
	std::string Y = "  Y: " + std::to_string(player.GetPosition().y);

	fpsText.setString(FPS + X + Y);
}

void Game::Draw()
{
	window.clear();

	window.draw(sky1);
	window.draw(sky2);

	rayCaster.Draw();

	level.Draw(window);
	player.Draw(window);
	
	window.draw(fpsText);

	window.display();
}
