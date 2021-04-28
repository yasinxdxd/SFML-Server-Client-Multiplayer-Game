#ifndef REMOTE_PLAYER_H
#define REMOTE_PLAYER_H

#include <Entity.h>

class RemotePlayer : public Entity
{
public:
	RemotePlayer(std::string name);

public:
	void update(const sf::Vector2f& pos);
	void draw(sf::RenderWindow& window) override;

private:
	

};

#endif//REMOTE_PLAYER_H
