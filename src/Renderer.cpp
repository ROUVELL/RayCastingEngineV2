#include <algorithm>
#include "Renderer.h"

Renderer::Renderer(sf::RenderWindow* window,
				   Player* player, Level* level,
				   SpriteHandler* spriteHandler,
				   RayCasting* rayCaster)
	: window(window), player(player), level(level),
	rayCaster(rayCaster), spriteHandler(spriteHandler),
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

	GetObjectsToRender();
	UpdateDebugText(dt);
}

void Renderer::DrawAll() const
{
	window->draw(sky1);
	window->draw(sky2);

	//rayCaster->Draw3D();
	for (auto& renderData : toRender)
		window->draw(renderData.sprite);
	
	if (drawMiniMap)
	{
		level->Draw(*window);
		rayCaster->Draw(*window);
		spriteHandler->Draw(*window);
		player->Draw(*window);
	}

	window->draw(debugText);
}

void Renderer::GetObjectsToRender()
{
	toRender.clear();

	auto& walls = rayCaster->GetWalls();

	toRender.insert(toRender.end(), walls.begin(), walls.end());
	
	auto& sprites = spriteHandler->GetRenderData();
	
	// якщо немаЇ спрайт≥в то сортувати не потр≥бно. —кор≥ш за все ц€
	// ц€ оптим≥зац≥€ немаЇ сенсу тому що спрайти будуть повсюду
	if (sprites.size() > 0)
	{
		toRender.insert(toRender.end(), sprites.begin(), sprites.end());

		std::sort(toRender.begin(), toRender.end(), DepthComparison);
	}
}

void Renderer::UpdateDebugText(float dt)
{
	std::string FPS = std::to_string((int)(1.f / dt));
	std::string X = "\n\nX: " + std::to_string(player->GetPosition().x);
	std::string Y = "  Y: " + std::to_string(player->GetPosition().y);
	std::string angle = "\nAngle: " + std::to_string(player->GetAngle() * 180.f / Settings::PI);

	debugText.setString(FPS + X + Y + angle);
}

bool DepthComparison(const RenderData& left, const RenderData& right)
{
	return left.depth > right.depth;
}
