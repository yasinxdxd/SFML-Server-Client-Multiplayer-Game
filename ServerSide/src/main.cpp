#include <Server.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>

struct S_Player
{
	float a, b, c, d, e, f;
	sf::CircleShape cir;
};

struct S_Client
{
	sf::UdpSocket udp;
	//Server::net net;
};


int main(int argc, char* argv[])
{
	/**/
	sf::RenderWindow window(sf::VideoMode(800, 600), "SERVER", sf::Style::Close | sf::Style::Titlebar);
	sf::Event event;
	Server GameServer(50000);
	/**/

	std::vector<std::shared_ptr<S_Player>> players;
	

	while (window.isOpen())
	{
		/////////////////////////////////////////////////////////////
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			break;
		}
		//////////////////////////////////////////////////////////////	


		GameServer.Run();


		
		for (auto& p : players)
		{
			window.clear();
			window.draw(p->cir);
			window.display();
		}

	}


	return 0;
}