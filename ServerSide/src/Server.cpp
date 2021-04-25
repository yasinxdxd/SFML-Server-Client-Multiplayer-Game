#include <Server.h>

Server::Server(const unsigned short& PORT):
	serverIP("192.168.1.105")
{
	this->PORT = PORT;
	if (socket.bind(this->PORT, serverIP) != sf::Socket::Done)
		printf("[-]Server couldn't bind : port %d\n", this->PORT);
	else
		printf("[+]Server binded : port %d\n", this->PORT);
}

void Server::Receive(sf::Packet& packet, sf::IpAddress& ip_address) noexcept
{
	if (socket.receive(packet, ip_address, PORT) != sf::Socket::Done)
	{
		printf("[-]Server couldn't receive data from %s address\n", ip_address.toString().data());
		return;
	}
	//printf("[+]Server recieved data from %s\n", ip_address.toString().data());
}

void Server::Send(sf::Packet& packet, sf::IpAddress& ip_address) noexcept
{
	if (socket.send(packet, ip_address, PORT) != sf::Socket::Done)
	{
		printf("[-]Server couldn't send data to %s address\n", ip_address.toString().data());
		return;
	}
	printf("[+]Server sent data to %s\n", ip_address.toString().data());
}

bool Server::Disconnect(sf::IpAddress& ip_address)
{
	printf("[-]%s : Disconnected from Server", ip_address.toString().data());
	client_array.erase(client_array.find(ip_address));
	return true;
}

void Server::ManageRecievedPacketsAndIpAdresses()
{
	// create packet and ip
	sf::Packet pck;
	sf::IpAddress ip;

	// wait for the data from client
	Receive(pck, ip);
	DATA data {};

	
	// check is there a new client.
	if (client_array.empty() || Search(client_array, ip))// if there is no same address before.
	{
		std::pair<sf::IpAddress, sf::Packet> new_client(ip, pck);
		client_array.insert(std::move(new_client));
		client_array.at(ip) = std::move(pck);
		client_array.at(ip) >> data.is_connected >> data.player_name >> data.player_x >> data.player_y;
		printf("[+]New client joined to the server : %s\n", ip.toString().data());
	}
	else// set the packet of the particular address.
	{
		client_array.at(ip) = std::move(pck);
		client_array.at(ip) >> data.is_connected >> data.player_name >> data.player_x >> data.player_y;
		/*
		printf("*Connected: %d\n", data.is_connected);
		printf("*Name:      %s\n", data.player_name.data());
		printf("*PlayerX:   %1.f\n", data.player_x);
		printf("*PlayerY:   %1.f\n", data.player_y);
		*/
	}
	if (data.is_connected == 0)// erase the client from map.
	{
		Disconnect(ip);
	}
	

}

void Server::ManageSentPacketsAndIpAdresses()
{
	for (auto& r_client : client_array)
	{
		for (auto& s_client : client_array)
		{
			if (r_client.first != s_client.first)
			{
				sf::Packet packet = s_client.second;
				sf::IpAddress ip = r_client.first;
				Send(packet, ip);
			}
		}
	}

}

bool Server::Search(std::map<sf::IpAddress, sf::Packet>& mymap, sf::IpAddress key)
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

void Server::Run()
{
	ManageRecievedPacketsAndIpAdresses();
	ManageSentPacketsAndIpAdresses();
}
