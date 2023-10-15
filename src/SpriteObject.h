#pragma once

#include "Player.h"
#include "RenderData.h"

class SpriteObject
{
public:
	SpriteObject(Player* player,
				 Level* level);
	virtual ~SpriteObject() {};

	void SetPosition(sf::Vector2f& position) { this->position = position; }
	void SetScale(float scale) { this->scale = scale; }
	void SetShift(float shift) { this->shift = shift; }

	// Метод перевіряє чи потрібно додавати об'єкт до рендер-списку
	bool CheckObject();
	RenderData GetRenderData() const { return RenderData(dist, sprite); };

	virtual void Update() = 0;
	// on Minimap !
	void Draw(sf::RenderTarget& target) const;

protected:
	Player* player;
	Level* level;

	sf::Texture* texture = nullptr;

	sf::Vector2f position;  // on map
	float shift = 0.f;
	float scale = 1.f;

	float dist = 1.f;  // from player
	float normDist = 1.f;
	float screenX = 0.f;  // position on screen

	void SetTexture(sf::Texture* newTexture = nullptr);

private:
	sf::Sprite sprite;

	float textureWidth = 0.f;
	float textureHalfWidth = 0.f;
	float textureHeight = 0.f;
	float textureRation = 0.f;

	// Метод оновлює позицію та розмір спрайта на екрані
	void UpdateProjection();
};

