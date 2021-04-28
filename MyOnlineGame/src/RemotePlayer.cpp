#include <RemotePlayer.h>

RemotePlayer::RemotePlayer(std::string name) :
	Entity(name)
{
	speed.x = 10;
	speed.y = 10;
}

void RemotePlayer::update(const sf::Vector2f& position)
{
	m_sprite.setPosition(position);
}

void RemotePlayer::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}
