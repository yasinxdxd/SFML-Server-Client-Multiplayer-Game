#include <Client.h>
#include <Game.h>
#include <thread>


Client::Client(const unsigned short& PORT, sf::IpAddress& ServerIP, sf::IpAddress ClientIP, std::string player_name):
	isConnected(true),
	player(std::make_shared<Player>(player_name)),
	ServerIP(ServerIP),
	ClientIP(ClientIP)
{
	Init(PORT);
}

Client::Client(const unsigned short& PORT, sf::IpAddress ServerIP, sf::IpAddress ClientIP, std::string player_name):
	isConnected(true),
	player(std::make_shared<Player>(player_name)),
	ServerIP(ServerIP),
	ClientIP(ClientIP)
{
	Init(PORT);
}

void Client::Init(const unsigned short& PORT)
{
	this->PORT = PORT;
	
	
	if (socket.bind(this->PORT, ClientIP) != sf::Socket::Done)
		printf("[-]r:Client couldn't bind : port %d\n", this->PORT);
	else
		printf("[+]r:Client binded : port %d\n", this->PORT);
	
	
	
	
	
	

	//ManageSendingData();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	//recieve_thread = std::make_unique<std::thread>(std::thread(&Client::ManageRecievingData, this));
	//send_thread = std::make_unique<std::thread>(std::thread(&Client::ManageSendingData, this));
	
	printf("[+]Client is running...:%s\n", ClientIP.toString().data());
}

Client::~Client()
{
	//delete recieve_thread;
	//delete send_thread;
}

void Client::Run() noexcept
{
	/*
	Client: first recieve, then send.
	*/
	ManageSendingData();
	//if (recieve_thread->joinable())
		//recieve_thread->join();
	ManageRecievingData();
	//if (send_thread->joinable())
		//send_thread->join();
}

void Client::Disconnect() noexcept
{
	isConnected = false;
	Run();
	printf("[-]Disconnected from Server : %s", ServerIP.toString().data());
}

bool Client::GetStatus() noexcept
{
	return isConnected;
}

void Client::Recieve(sf::Packet& packet, sf::IpAddress& ip_address)
{
	//std::this_thread::sleep_for(std::chrono::milliseconds(10));
	unsigned short port;
	auto status = socket.receive(packet, ip_address, port);
	if (status == sf::Socket::Error)
	{
		printf("[-]ERROR! Recieving data from %s address\n", ip_address.toString().data());
		return;
	}
	else if (status == sf::Socket::NotReady)
	{
		printf("[-]Client is not ready to recieve data from %s address\n", ip_address.toString().data());
		return;
	}
	else if (status != sf::Socket::Done)
	{
		printf("[-]Client couldn't receive data from %s address\n", ip_address.toString().data());
		return;
	}
	//printf("[+]Client recieved data to %s\n", ip_address.toString().data());
}

void Client::Send(sf::Packet& packet, sf::IpAddress& ip_address)
{
	if (socket.send(packet, ip_address, 50000) != sf::Socket::Done)
	{
		printf("[-]Client couldn't send data to %s address\n", ip_address.toString().data());
		return;
	}
	//printf("[+]Client sent data to %s\n", ip_address.toString().data());
}

void Client::ManageSendingData()
{
	//player update:
	player->update();

	packetSend << GetStatus() << ClientIP.toString() << player->name << player->pos.x << player->pos.y;
	Send(packetSend, ServerIP);
	packetSend.clear();

}

void Client::ManageRecievingData()
{
	sf::IpAddress ip; // it is going to come from the Server.
	sf::Packet packet;
	
	Recieve(packet, ip);
	//printf("............................%s",ip.toString().c_str());
	DATA data{};
	packet >> data.is_connected >> data.ip_address >> data.player_name >> data.player_x >> data.player_y;
	//printf("x: %1.f\n", data.player_x);
	
	// check is there a new player.
	if (remote_players.empty() || Search(remote_players, sf::IpAddress(data.ip_address)))// if there is no same address before.
	{
		std::pair<sf::IpAddress, std::shared_ptr<RemotePlayer>> r_player(sf::IpAddress(data.ip_address), std::make_shared<RemotePlayer>(data.player_name));
		remote_players.insert(std::move(r_player));
		printf("[+]New player joined to the game : %s\n", data.player_name.data());
		for (auto& [rp_ip, rp_player] : remote_players)
		{
			rp_player->m_texture.loadFromFile("resource/assets/Robot 1/robot1_hold.png");
			rp_player->m_sprite.setTexture(rp_player->m_texture);
		}
	}
	
	
	//remote_players update:
	for (auto& [ip, r_player] : remote_players)
		r_player->update(sf::Vector2f(data.player_x, data.player_y));
}

bool Client::Search(std::map<sf::IpAddress, std::shared_ptr<RemotePlayer>>& mymap, sf::IpAddress key)
{
	auto it = mymap.begin();

	for (it; it != mymap.end(); it++)
	{
		if (key == it->first)
		{
			return false;
		}
	}
	return true;
}
