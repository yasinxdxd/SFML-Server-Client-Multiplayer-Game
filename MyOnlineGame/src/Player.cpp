#include <Player.h>

Player::Player(std::string name):
	Entity(name)
{
	speed.x = 10;
	speed.y = 10;
}

void Player::update()
{
	move();
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

void Player::move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		pos.y -= speed.y;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		pos.y += speed.y;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		pos.x -= speed.x;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		pos.x += speed.x;
	}

	m_sprite.setPosition(pos);
}

