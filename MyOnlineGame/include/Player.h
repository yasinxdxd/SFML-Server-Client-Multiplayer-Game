#ifndef PLAYER_H
#define PLAYER_H

#include <Entity.h>

class Player : public Entity
{
public:
	Player(std::string name);

public:
	void update() override;
	void draw(sf::RenderWindow& window) override;

private:
	void move();

};

#endif//PLAYER_H
