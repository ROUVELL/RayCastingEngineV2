#include "RayCasting.h"


RayCasting::RayCasting(sf::RenderWindow* window, Player* player, Level* level)
	: window(window), player(player), level(level)
{
	for (uint i = 0; i < Settings::TEXTURES_COUNT; i++)
	{
		textures[i].loadFromFile(Settings::TEXTURES_DIR + std::to_string(i) + ".png");
		/*sf::Vector2u size = textures[i].getSize();
		sf::Vector2f scale((float)Settings::TEXTURE_SIZE / size.x,
						   (float)Settings::TEXTURE_SIZE / size.y);*/
		textures[i].setRepeated(true);
	}
}

void RayCasting::Update()
{
	sf::Vector2f pos = this->player->GetPosition();
	sf::Vector2i ipos = sf::Vector2i(pos);
	sf::Vector2u levelSize = level->GetSize();
	uint vTexNum, hTexNum;

	float rayAngle = this->player->GetAngle() - Settings::H_FOV + 0.0001f;
	for (int ray = 0; ray < Settings::NUM_RAYS; ray++)
	{
		float sin_a = std::sin(rayAngle);
		float cos_a = std::cos(rayAngle);

		vTexNum = -1;
		hTexNum = -1;

		// horizontals
		float yHor, horDy;
		if (sin_a > 0)
		{
			yHor = ipos.y + 1.f;
			horDy = 1.f;
		}
		else
		{
			yHor = ipos.y - 1e-5f;
			horDy = -1.f;
		}

		float depthHor = (yHor - pos.y) / sin_a;
		float xHor = pos.x + depthHor * cos_a;

		float horDeltaDepth = horDy / sin_a;
		float horDx = horDeltaDepth * cos_a;

		for (uint i = 0; i < levelSize.y; i++)
		{
			
			if (!this->level->IsEmpty((int)xHor, (int)yHor))
			{
				hTexNum = this->level->Get((int)xHor, (int)yHor) - 1;
				break;
			}

			xHor += horDx;
			yHor += horDy;
			depthHor += horDeltaDepth;
		}

		// verticals
		float xVert, vertDx;
		if (cos_a > 0)
		{
			xVert = ipos.x + 1.f;
			vertDx = 1.f;
		}
		else
		{
			/*
			Раніше тут було 1е-6f, але коли позиція по х була більше 32
			промені заходили всередину стін, тому я опустив до 1е-5f
			*/
			xVert = ipos.x - 1e-5f;
			vertDx = -1.f;
		}

		float depthVert = (xVert - pos.x) / cos_a;
		float yVert = pos.y + depthVert * sin_a;

		float vertDeltaDepth = vertDx / cos_a;
		float vertDy = vertDeltaDepth * sin_a;

		for (uint i = 0; i < levelSize.x; i++)
		{
			if (!this->level->IsEmpty((int)xVert, (int)yVert))
			{
				vTexNum = this->level->Get((int)xVert, (int)yVert) - 1;
				break;
			}

			xVert += vertDx;
			yVert += vertDy;
			depthVert += vertDeltaDepth;
		}

		float depth, offset;
		int texNum;
		if (depthVert < depthHor)
		{
			depth = depthVert;
			texNum = vTexNum;
			yVert = std::fmodf(yVert, 1.f);
			offset = cos_a > 0 ? yVert : (1.f - yVert);
		}
		else
		{
			depth = depthHor;
			texNum = hTexNum;
			xHor = std::fmodf(xHor, 1.f);
			offset = sin_a > 0 ? (1.f - xHor) : xHor;
		}

		if (texNum >= 0)
		{
			depth *= std::cos(this->player->GetAngle() - rayAngle);
			float projHeight = Settings::SCREEN_DIST / (depth + 0.0001f);

			raysData[ray].rayNum = ray;
			raysData[ray].depth = depth;
			raysData[ray].projHeight = projHeight;
			raysData[ray].texNum = texNum;
			raysData[ray].offset = offset;
			raysData[ray].angle = rayAngle;
		}
		else
			raysData[ray].texNum = -1;

		rayAngle += Settings::DELTA_ANGLE;
	}
}

void RayCasting::Draw2D() const
{
	sf::VertexArray lines(sf::Lines, 2);

	float playerAngle = player->GetAngle();
	sf::Vector2f playerPos = player->GetMappedPosition();
	playerPos.y += level->GetOffsetY();

	for (auto& ray : raysData)
	{
		if (ray.texNum == -1)
			continue;

		float depth = ray.depth / std::cos(playerAngle - ray.angle);
		sf::Vector2f end(
			playerPos.x + depth * Settings::TILE_SIZE * std::cos(ray.angle),
			playerPos.y + depth * Settings::TILE_SIZE * std::sin(ray.angle)
		);

		lines.append(sf::Vertex(playerPos, sf::Color(255, 255, 255, 60)));
		lines.append(sf::Vertex(end, sf::Color(255, 255, 255, 60)));
	}

	window->draw(lines);
}

void RayCasting::Draw3D() const
{
	sf::Sprite wall;

	for (auto& ray : raysData)
	{
		if (ray.texNum == -1)
			continue;

		wall.setTexture(textures[ray.texNum]);

		int left = static_cast<int>(ray.offset * (Settings::TEXTURE_SIZE - Settings::SCALE));
		int top = static_cast<int>(Settings::H_SCREEN_HEIGHT - ray.projHeight / 2.f);

		wall.setPosition(ray.rayNum * (float)Settings::SCALE, (float)top);
		wall.setScale(1.f, ray.projHeight / (float)Settings::TEXTURE_SIZE);
		wall.setTextureRect(sf::IntRect(left, 0, Settings::SCALE, Settings::TEXTURE_SIZE));

		window->draw(wall);
	}
}
