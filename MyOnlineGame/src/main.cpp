#include <Game.h>
#include <stdio.h>
#include <iostream>


int main(int argc, char* argv[])
{	
	unsigned short PORT;
	std::string ClientIP;
	std::string player_name = "noname";
	std::cout << "IP Address : ";
	std::cin.getline(ClientIP.data(), 100);
	std::cout << "Player Name : ";
	std::cin.getline(player_name.data(), 100);
	std::cout << "PORT : ";
	std::cin >> PORT;
	Game game(PORT, sf::IpAddress(ClientIP), player_name);
	game.update();



	return 0;
}