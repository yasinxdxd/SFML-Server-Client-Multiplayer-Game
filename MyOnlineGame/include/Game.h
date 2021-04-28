#ifndef GAME_H
#define GAME_H

#include <Client.h>
#include <vector>
#include <memory>

class Game final
{
public:
	Game(const unsigned short& PORT, sf::IpAddress Client_IP, std::string player_name);
	~Game();

	void update();

private:
	void eventUpdate();
	void draw();


private:
	sf::RenderWindow m_window;
	sf::Event event;
	Client GameClient;

};


#endif//GAME_H
