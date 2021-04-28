#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>
#include <Player.h>
#include <RemotePlayer.h>
#include <map>
#include <thread>

#define SERVER_IP "192.168.1.105"//"25.97.120.215"
#define CLIENT_IP "192.168.1.105"//"25.97.120.215"

class Game;

class Client final
{
public:
	Client(const unsigned short& PORT, sf::IpAddress& ServerIP, sf::IpAddress ClientIP, std::string player_name);
	Client(const unsigned short& PORT, sf::IpAddress ServerIP, sf::IpAddress ClientIP, std::string player_name);
	~Client();
	void Run() noexcept;
	void Disconnect() noexcept;
	bool GetStatus() noexcept;

private:
	void Init(const unsigned short& PORT);
	void Recieve(sf::Packet& packet, sf::IpAddress& ip_address);
	void Send(sf::Packet& packet, sf::IpAddress& ip_address);

	void ManageSendingData();
	void ManageRecievingData();

	bool Search(std::map<sf::IpAddress, std::shared_ptr<RemotePlayer>>& mymap, sf::IpAddress key);

private:
	sf::UdpSocket socket;
	sf::IpAddress ClientIP;
	sf::IpAddress ServerIP;
	unsigned short PORT;
	bool isConnected;
	std::unique_ptr<std::thread> recieve_thread;
	std::unique_ptr<std::thread> send_thread;

public:
	sf::Packet packetSend;

	std::shared_ptr<Player> player;
	std::map<sf::IpAddress, std::shared_ptr<RemotePlayer>> remote_players;
};

#if 1
struct DATA
{
	bool is_connected;
	std::string ip_address;
	std::string player_name;
	float player_x;
	float player_y;
};
#endif

#endif//CLIENT_H
