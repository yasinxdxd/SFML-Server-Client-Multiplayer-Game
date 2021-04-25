#ifndef GAME_H
#define GAME_H

#include <Player.h>
#include <vector>
#include <memory>

class Game final
{
public:
	Game(std::string player_name);
	~Game();

	void update();

private:
	void eventUpdate();
	void draw();

public:
	void ManageSendingData() noexcept;
	void ManageRecievingData() noexcept;


private:
	sf::RenderWindow m_window;
	sf::Event event;
	std::shared_ptr<Entity> player;

	std::vector<std::shared_ptr<Entity>> entities;

	Client GameClient;

};


#endif//GAME_H
