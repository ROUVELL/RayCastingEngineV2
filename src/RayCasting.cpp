#include "RayCasting.h"


RayCasting::RayCasting(sf::RenderWindow* window, Player* player, Level* level)
	: window(window), player(player), level(level)
{
	for (int i = 0; i < Settings::TEXTURES_COUNT;)
		textures[i].loadFromFile(Settings::TEXTURES_DIR + std::to_string(++i) + ".png");
}

void RayCasting::Update()
{
	sf::Vector2f pos = this->player->GetPosition();
	sf::Vector2i ipos = sf::Vector2i(pos);
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
			yHor = ipos.y - 1e-5;
			horDy = -1.f;
		}

		float depthHor = (yHor - pos.y) / sin_a;
		float xHor = pos.x + depthHor * cos_a;

		float horDeltaDepth = horDy / sin_a;
		float horDx = horDeltaDepth * cos_a;

		for (int i = 0; i < Settings::LEVEL_HEIGHT; i++)
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
			Раніше тут було 1е-6, але коли позиція по х була більше 32
			промені заходили всередину стін, тому я опустив до 1е-5
			*/
			xVert = ipos.x - 1e-5;
			vertDx = -1.f;
		}

		float depthVert = (xVert - pos.x) / cos_a;
		float yVert = pos.y + depthVert * sin_a;

		float vertDeltaDepth = vertDx / cos_a;
		float vertDy = vertDeltaDepth * sin_a;

		for (int i = 0; i < Settings::LEVEL_WIDTH; i++)
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
			//depth *= std::cos(this->player->GetAngle() - rayAngle);
			float projHeight = Settings::SCREEN_DIST / (depth + 0.0001f);

			raysData[ray].rayNum = ray;
			raysData[ray].depth = depth;
			raysData[ray].projHeight = projHeight;
			raysData[ray].texNum = texNum;
			raysData[ray].offset = offset;
			raysData[ray].rayAngle = rayAngle;
		}
		else
			raysData[ray].texNum = -1;

		rayAngle += Settings::DELTA_ANGLE;
	}
}

void RayCasting::Draw()
{
	sf::VertexArray lines(sf::Lines, 2);
	sf::Sprite wall;

	for (auto& ray : raysData)
	{
		if (ray.texNum == -1)
			continue;


		sf::Vector2f p_pos = player->GetMappedPosition();
		sf::Vector2f end(
			p_pos.x + ray.depth * Settings::TILE_SIZE * std::cos(ray.rayAngle),
			p_pos.y + ray.depth * Settings::TILE_SIZE * std::sin(ray.rayAngle)
		);

		lines.append(sf::Vertex(p_pos, sf::Color(255, 255, 255, 60)));
		lines.append(sf::Vertex(end, sf::Color(255, 255, 255, 60)));


		wall.setTexture(textures[ray.texNum]);

		int left = static_cast<int>(ray.offset * (Settings::TEXTURE_SIZE - Settings::SCALE));
		int top = static_cast<int>(Settings::H_SCREEN_HEIGHT - ray.projHeight / 2.f);

		wall.setPosition(ray.rayNum * (float)Settings::SCALE, (float)top);
		wall.setScale(1.f, ray.projHeight / (float)Settings::TEXTURE_SIZE);
		wall.setTextureRect(sf::IntRect(left, 0, Settings::SCALE, Settings::TEXTURE_SIZE));

		window->draw(wall);
	}

	window->draw(lines);
}
