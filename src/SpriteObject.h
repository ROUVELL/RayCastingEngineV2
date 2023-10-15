#pragma once

#include "Player.h"
#include "RenderData.h"

class SpriteObject
{
public:
	SpriteObject(Player* player,
				 Level* level,
				 sf::Vector2f position);
	SpriteObject(Player* player,
				 Level* level,
				 sf::Vector2f position,
				 std::string filename);
	~SpriteObject();

	// Метод перевіряє чи потрібно додавати об'єкт до рендер-списку
	bool CheckObject();

	RenderData GetRenderData() const { return RenderData(dist, sprite); };

	// on Minimap !
	void Draw(sf::RenderTarget& target) const;

protected:
	Player* player;
	Level* level;

	sf::Vector2f position;  // on map
	sf::Texture* texture;
	sf::Sprite sprite;

	float textureWidth;
	float textureHalfWidth;
	float textureHeight;
	float textureRation;

	float dist;  // from player
	float normDist;
	float screenX;  // position on screen

	void SetTexture(sf::Texture& newTexture);

private:
	// Метод оновлює спрайт
	void UpdateProjection();
};

