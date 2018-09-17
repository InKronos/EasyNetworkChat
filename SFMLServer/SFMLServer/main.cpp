#include <SFML/Network.hpp>
#include <iostream>
#include <Windows.h>
#include <string>

int main()
{
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect("192.168.1.101", 53000);
	std::size_t received;

	char ConnectionType, mode;
	char buffer[2000];
	std::cout << "Type s for server, c for client" << std::endl;
	std::cin >> ConnectionType;
	std::string data;
	data = "you are connected";

	if (ConnectionType == 's')
	{
		sf::TcpListener listener;
		listener.listen(2000);
		listener.accept(socket);
		data += " to server";
		mode = 's';
	}
	else 
	{
		socket.connect("192.168.1.101", 2000);
		data += " to client";
		mode = 'r';
	}

	if (socket.send(data.c_str(), data.length() + 1) != sf::Socket::Done)
	{
		// error...
	}
	socket.receive(buffer, sizeof(buffer), received);
	std::cout << "Received: " << buffer << std::endl;

	bool done = false;

	while (!done)
	{
		if (mode == 's')
		{
			std::getline(std::cin, data);
			socket.send(data.c_str(), data.length() + 1);
			mode = 'r';
		}
		else
		{
			socket.receive(buffer, sizeof(buffer), received);
			if (received > 0)
			{
				std::cout << "Received: " << buffer << std::endl;
				mode = 's';
			}
		}
	}

	if (status != sf::Socket::Done)
	{
		// error...
	}
}