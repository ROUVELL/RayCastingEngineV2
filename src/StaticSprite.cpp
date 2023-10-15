#include "StaticSprite.h"

StaticSprite::StaticSprite(Player* player, Level* level, std::string filename)
	: SpriteObject(player, level)
{
	this->texture = new sf::Texture{};
	this->texture->loadFromFile(Settings::STATIC_SPRITES_DIR + filename);
	SetTexture();
}

StaticSprite::~StaticSprite()
{
	delete this->texture;
	this->texture = nullptr;
}
