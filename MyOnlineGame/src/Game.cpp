#include <Game.h>
#include <Windows.h>
#include <chrono>
#include <thread>

Game::Game(std::string player_name) :
	m_window(sf::VideoMode(800, 600), "MyGame", sf::Style::Close | sf::Style::Titlebar),
	player(std::make_shared<Player>(player_name)),
	GameClient(50000, sf::IpAddress("192.168.1.105"))
{
	//window properities
	m_window.setFramerateLimit(60);

	player->m_texture.loadFromFile("resource/assets/Soldier 1/soldier1_hold.png");
	player->m_sprite.setTexture(player->m_texture);

	
}

Game::~Game()
{

}

void Game::update()
{
	while (m_window.isOpen())
	{
		eventUpdate();
		
		//player update:
		player->update();

		
		GameClient.Run(this);
		

		
		//game draw:
		draw();
	}
	GameClient.Disconnect(this);
	std::this_thread::sleep_for(std::chrono::seconds(1));

}

void Game::draw()
{
	m_window.clear();
	player->draw(m_window);
	m_window.display();
}

void Game::ManageSendingData() noexcept
{
	GameClient.packetSend
		<< GameClient.GetStatus()
		<< player->name
		<< player->pos.x
		<< player->pos.y;

}

void Game::ManageRecievingData() noexcept
{
	bool b;
	std::string n;
	float x, y;
	GameClient.packetRecieve
		>> b
		>> n
		>> x >> y;
	printf("x: %1.f\n", x);
	printf("y: %1.f\n", y);
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
