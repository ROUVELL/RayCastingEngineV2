#include "Renderer.h"

Renderer::Renderer(sf::RenderWindow* window,
				   Player* player, Level* level,
				   RayCasting* rayCaster)
	: window(window), player(player), level(level), rayCaster(rayCaster),
	skyOffset(0.f), drawMiniMap(false)
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
}

void Renderer::Update(float dt)
{
	skyOffset = std::fmodf(skyOffset + Settings::SCREEN_WIDTH + 4.f * player->GetRel(), (float)Settings::SCREEN_WIDTH);
	sky1.setPosition(-skyOffset, 0.f);
	sky2.setPosition(-skyOffset + Settings::SCREEN_WIDTH, 0.f);

	std::string FPS = std::to_string((int)(1.f / dt));
	std::string X = "\n\nX: " + std::to_string(player->GetPosition().x);
	std::string Y = "  Y: " + std::to_string(player->GetPosition().y);
	std::string angle = "\nAngle: " + std::to_string(player->GetAngle() * 180.f / Settings::PI);

	debugText.setString(FPS + X + Y + angle);
}

void Renderer::DrawAll() const
{
	window->draw(sky1);
	window->draw(sky2);

	rayCaster->Draw3D();

	if (drawMiniMap)
	{
		level->Draw(*window);
		rayCaster->Draw2D();
		player->Draw(*window);
	}

	window->draw(debugText);
}
