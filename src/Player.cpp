#include "Player.h"

Player::Player(Level* level)
	: level(level), position(Settings::PLAYER_POS), angle(0.f)
{
}


void Player::ProcessEvents(sf::Event& event)
{
}

void Player::Update(float dt)
{
	Rotate(dt);
	Movement(dt);
}

void Player::Draw(sf::RenderWindow& window) const
{
	sf::Vector2f mappedPos = GetMappedPosition();
	sf::Vector2f endpoint(mappedPos.x + std::cos(angle) * Settings::H_SCREEN_WIDTH,
						  mappedPos.y + std::sin(angle) * Settings::H_SCREEN_WIDTH);

	sf::VertexArray line(sf::Lines, 2);
	line[0] = sf::Vertex(mappedPos, sf::Color::Red);
	line[1] = sf::Vertex(endpoint, sf::Color::Red);;
	
	window.draw(line);

	sf::CircleShape player(10.f, 10);
	player.setFillColor(sf::Color::Green);
	player.setOrigin(10.f, 10.f);
	player.setPosition(mappedPos);

	window.draw(player);
}

void Player::Movement(float dt)
{
	direction.x = 0.f;
	direction.y = 0.f;

	float speed = Settings::PLAYER_SPEED * dt;
	float sinSpeed = speed * std::sin(angle);
	float cosSpeed = speed * std::cos(angle);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		direction.x += cosSpeed;
		direction.y += sinSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		direction.x -= cosSpeed;
		direction.y -= sinSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		direction.x += sinSpeed;
		direction.y -= cosSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		direction.x -= sinSpeed;
		direction.y += cosSpeed;
	}

	CheckCollision(dt);

	position += direction;
}

void Player::Rotate(float dt)
{
	rel = (float)GetMouseOffset();
	angle += rel * Settings::MOUSE_SENSETIVITY * dt;
	angle = fmodf(angle, Settings::DOUBLE_PI);
}

void Player::CheckCollision(float dt)
{
	float scale = 1.f;

	if (!level->IsEmpty((int)(position.x + direction.x * scale), (int)position.y))
		direction.x = 0;

	if (!level->IsEmpty((int)position.x, (int)(position.y + direction.y * scale)))
		direction.y = 0;
}

int GetMouseOffset()
{
	static bool firstFrame = true;

	if (firstFrame)
	{
		sf::Mouse::setPosition(sf::Vector2i(Settings::H_MONITOR_WIDTH, Settings::H_MONITOR_HEIGHT));
		firstFrame = false;
		return 0;
	}

	int offset = sf::Mouse::getPosition().x - (int)Settings::H_MONITOR_WIDTH;
	sf::Mouse::setPosition(sf::Vector2i(Settings::H_MONITOR_WIDTH, Settings::H_MONITOR_HEIGHT));
	return std::min(std::max(offset, -Settings::MAX_REL), Settings::MAX_REL);
}
