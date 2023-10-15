#include <iostream>
#include <cmath>

#include "SpriteObject.h"

SpriteObject::SpriteObject(Player* player, Level* level, sf::Vector2f position)
	: player(player), level(level), position(position), texture(nullptr),
	textureWidth(0.f), textureHalfWidth(0.f), textureHeight(0.f),
	textureRation(1.f), dist(1.f), normDist(1.f), screenX(0.f)
{
}

SpriteObject::SpriteObject(Player* player, Level* level, sf::Vector2f position, std::string filename)
	: SpriteObject(player, level, position)
{
	this->texture = new sf::Texture{};
	this->texture->loadFromFile(filename);
	SetTexture(*this->texture);
	this->sprite.setOrigin(this->textureHalfWidth, this->textureHeight / 2.f);
}

SpriteObject::~SpriteObject()
{
	delete this->texture;
	this->texture = nullptr;
}

bool SpriteObject::CheckObject()
{
	sf::Vector2f distance = this->position - this->player->GetPosition();
	
	float theta = std::atan2(distance.y, distance.x);

	float delta = theta - this->player->GetAngle();
	if ((distance.x > 0 && this->player->GetAngle() > Settings::PI)
		|| (distance.x < 0 && distance.y < 0))
		delta += Settings::DOUBLE_PI;

	float deltaRays = delta / Settings::DELTA_ANGLE;
	this->screenX = ((float)Settings::H_NUM_RAYS + deltaRays) * (float)Settings::SCALE;

	this->dist = std::hypot(distance.x, distance.y);
	this->normDist = this->dist * std::cos(delta);

	if ((-this->textureHalfWidth < this->screenX && this->screenX < (Settings::SCREEN_WIDTH + this->textureHalfWidth))
		&& this->normDist > 0.5f)
	{
		UpdateProjection();
		return true;
	}

	return false;
}

void SpriteObject::Draw(sf::RenderTarget& target) const
{
	sf::CircleShape sprite(5.f, 6);
	sprite.setFillColor(sf::Color::Yellow);
	sprite.setOrigin(5.f, 5.f);
	sprite.setPosition(
		this->position.x * Settings::TILE_SIZE,
		this->position.y * Settings::TILE_SIZE + this->level->GetOffsetY()
	);

	target.draw(sprite);
}

void SpriteObject::UpdateProjection()
{
	float proj = Settings::SCREEN_DIST / this->normDist;
	float projWidth = proj * this->textureRation;
	
	float scaleX = projWidth / this->textureWidth;
	float scaleY = proj / this->textureHeight;

	sprite.setScale(scaleX, scaleY);
	sprite.setPosition(
		this->screenX,
		(float)Settings::H_SCREEN_HEIGHT
	);
}

void SpriteObject::SetTexture(sf::Texture& newTexture)
{
	*this->texture = newTexture;
	this->sprite.setTexture(*this->texture);

	sf::Vector2f size = (sf::Vector2f)this->texture->getSize();
	this->textureWidth = size.x;
	this->textureHalfWidth = this->textureWidth / 2.f;
	this->textureHeight = size.y;
	this->textureRation = this->textureWidth / (float)this->texture->getSize().y;
}

