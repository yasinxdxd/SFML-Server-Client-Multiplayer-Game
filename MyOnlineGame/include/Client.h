#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>
class Game;

class Client final
{
public:
	Client(const unsigned short& PORT, sf::IpAddress& Server);
	Client(const unsigned short& PORT, sf::IpAddress Server);
	void Run(Game* game) noexcept;
	void Disconnect(Game* game) noexcept;
	bool GetStatus() noexcept;

private:
	void Recieve(sf::Packet& packet, sf::IpAddress& ip_address) noexcept;
	void Send(sf::Packet& packet, sf::IpAddress& ip_address) noexcept;


private:
	sf::UdpSocket socket;
	sf::IpAddress ClientIP;
	sf::IpAddress ServerIP;
	unsigned short PORT;
	bool isConnected;

public:
	sf::Packet packetSend;
	sf::Packet packetRecieve;
};

#if 0
struct DATA
{
	bool is_connected;
	std::string player_name;
	float player_x;
	float player_y;
};
#endif

#endif//CLIENT_H
