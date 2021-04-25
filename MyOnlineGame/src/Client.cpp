#include <Client.h>
#include <Game.h>
#include <functional>

Client::Client(const unsigned short& PORT, sf::IpAddress& Server):
	isConnected(true)
{
	this->PORT = PORT;
	ClientIP = sf::IpAddress::getLocalAddress();
	ServerIP = Server;
	printf("[+]Client is running...\n");
}

Client::Client(const unsigned short& PORT, sf::IpAddress Server):
	isConnected(true)
{
	this->PORT = PORT;
	ClientIP = sf::IpAddress::getLocalAddress();
	ServerIP = Server;
	printf("[+]Client is running...\n");
}

void Client::Run(Game* game) noexcept
{
	game->ManageSendingData();
	Send(packetSend, ServerIP);
	packetSend.clear();

	sf::IpAddress ip; // it is going to come from the Server.
	Recieve(packetRecieve, ip);
	game->ManageRecievingData();
}

void Client::Disconnect(Game* game) noexcept
{
	isConnected = false;
	Run(game);
	printf("[-]Disconnected from Server : %s", ServerIP.toString().data());
}

bool Client::GetStatus() noexcept
{
	return isConnected;
}

void Client::Recieve(sf::Packet& packet, sf::IpAddress& ip_address) noexcept
{
	if (socket.receive(packet, ip_address, PORT) != sf::Socket::Done)
	{
		printf("[-]Client couldn't receive data from %s address\n", ip_address.toString().data());
		return;
	}
	printf("[+]Client recieved data to %s\n", ip_address.toString().data());
}

void Client::Send(sf::Packet& packet, sf::IpAddress& ip_address) noexcept
{
	if (socket.send(packet, ip_address, PORT) != sf::Socket::Done)
	{
		printf("[-]Client couldn't send data to %s address\n", ip_address.toString().data());
		return;
	}
	//printf("[+]Client sent data to %s\n", ip_address.toString().data());
}
