#include <Game.h>
#include <stdio.h>
#include <iostream>


int main(int argc, char* argv[])
{	
	std::string player_name = "noname";
	std::cin.getline(player_name.data(), 10);
	Game game(player_name);
	game.update();



	return 0;
}