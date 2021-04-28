#ifndef SERVER_H
#define SERVER_H

#include <SFML/Network.hpp>
#include <memory>
#include <thread>
#include <map>

#define SERVER_IP "192.168.1.105"//"25.97.120.215"

class Server final
{
public:
	Server(const unsigned short& PORT);
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

private:
	std::map<sf::IpAddress, sf::Packet> client_array;
	std::unique_ptr<std::thread> r_thread;
	std::unique_ptr<std::thread> s_thread;

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

#endif//SERVER_H
