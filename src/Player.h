#pragma once

#include "Level.h"

static int GetMouseOffset();

class Player
{
public:
	Player(Level* level);

	sf::Vector2f GetPosition() const { return position; }
	sf::Vector2i GetLevelPosition() const { return {(int)position.x, (int)position.y}; };
	sf::Vector2f GetMappedPosition() const { return {position.x * Settings::TILE_SIZE, position.y * Settings::TILE_SIZE}; }
	float GetAngle() const { return angle; }
	float GetRel() const { return rel; }

	void Update(float dt);
	void Draw(sf::RenderTarget& target) const;

private:
	Level* level;

	sf::Vector2f position;
	sf::Vector2f direction;
	float angle;
	float rel;

	void Movement(float dt);
	void Rotate(float dt);
	void CheckCollision(float dt);
};

