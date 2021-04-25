#ifndef SERVER_H
#define SERVER_H

#include <SFML/Network.hpp>
#include <memory>
#include <thread>
#include <map>

class Server final
{
public:
	Server(const unsigned short &PORT);
	void Run();

private:
	void Receive(sf::Packet& packet, sf::IpAddress& ip_address) noexcept;
	void Send(sf::Packet& packet, sf::IpAddress& ip_address) noexcept;
	bool Disconnect(sf::IpAddress& ip_address);

	void ManageRecievedPacketsAndIpAdresses();
	void ManageSentPacketsAndIpAdresses();

	bool Search(std::map<sf::IpAddress, sf::Packet>& mymap, sf::IpAddress key);

private:
	sf::UdpSocket socket;
	const sf::IpAddress serverIP;
	unsigned short PORT;

	std::map<sf::IpAddress, sf::Packet> client_array;

};


#if 1
struct DATA
{
	bool is_connected;
	std::string player_name;
	float player_x;
	float player_y;
};
#endif

#endif//SERVER_H
