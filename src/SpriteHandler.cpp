#include "LoopedSprite.h"
#include "SpriteHandler.h"

SpriteHandler::SpriteHandler(Player* player, Level* level) : player(player), level(level)
{
	std::string dirName = "greenLight";
	sf::Vector2f pos{16.5f, 6.5f};
	CreateLooped(pos, dirName, 4, 120);
}

SpriteHandler::~SpriteHandler()
{
	for (auto& sprite : sprites)
		delete sprite;
}

void SpriteHandler::CreateSprite(sf::Vector2f& position, std::string& filename,
								 float shift, float scale)
{
	StaticSprite* sprite = new StaticSprite(this->player, this->level, filename);
	sprite->SetShift(shift);
	sprite->SetScale(scale);
	sprite->SetPosition(position);
	sprites.push_back(sprite);
}

void SpriteHandler::CreateLooped(sf::Vector2f& position, std::string& dirName, uint count,
								 uint animTime, float shift, float scale)
{
	LoopedSprite* sprite = new LoopedSprite(this->player, this->level, dirName, count, animTime);
	sprite->SetShift(shift);
	sprite->SetScale(scale);
	sprite->SetPosition(position);
	sprites.push_back(sprite);
}

void SpriteHandler::Update()
{
	this->spritesRenderData.clear();

	for (auto& sprite : sprites)
	{
		sprite->Update();
		if (sprite->CheckObject())
			this->spritesRenderData.push_back(sprite->GetRenderData());
	}
}

void SpriteHandler::Draw(sf::RenderTarget& target) const
{
	for (auto& sprite : sprites)
		sprite->Draw(target);
}
