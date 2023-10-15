#include "SpriteHandler.h"

SpriteHandler::SpriteHandler(Player* player, Level* level) : player(player), level(level)
{
	sprites.push_back(new SpriteObject(this->player, this->level,
					  sf::Vector2f(20.5f, 8.5f), Settings::STATIC_SPRITES_DIR + "candlebra.png"));
}

SpriteHandler::~SpriteHandler()
{
	for (auto& sprite : sprites)
		delete sprite;
}

void SpriteHandler::Update()
{
	this->spritesRenderData.clear();

	for (auto& sprite : sprites)
	{
		if (sprite->CheckObject())
			this->spritesRenderData.push_back(sprite->GetRenderData());
	}
}

void SpriteHandler::Draw(sf::RenderTarget& target) const
{
	for (auto& sprite : sprites)
		sprite->Draw(target);
}
