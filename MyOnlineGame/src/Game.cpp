#include <Game.h>
#include <Windows.h>
#include <chrono>

Game::Game(const unsigned short& PORT, sf::IpAddress Client_IP, std::string player_name) :
	m_window(sf::VideoMode(800, 600), "MyGame", sf::Style::Close | sf::Style::Titlebar),
	GameClient(PORT, sf::IpAddress(SERVER_IP), Client_IP, player_name)
{
	//window properities
	m_window.setFramerateLimit(30);

	GameClient.player->m_texture.loadFromFile("resource/assets/Soldier 1/soldier1_hold.png");
	GameClient.player->m_sprite.setTexture(GameClient.player->m_texture);

	
}

Game::~Game()
{

}

void Game::update()
{
	while (m_window.isOpen())
	{
		eventUpdate();
		
		GameClient.Run();

		draw();
	}
	GameClient.Disconnect();
	std::this_thread::sleep_for(std::chrono::seconds(1));

}

void Game::draw()
{
	m_window.clear();
	//printf("%d\n", GameClient.remote_players.size());
	for (auto& [ip, r_player] : GameClient.remote_players)
		r_player->draw(m_window);
	GameClient.player->draw(m_window);
	m_window.display();
}

void Game::eventUpdate()
{
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}
}
