#include "stdafx.h"


Server::Server(int port)
{
	this->listener.listen(port);
	this->selector.add(this->listener);
	std::cout << "Server is working on port: " << port << std::endl;
}

Server::~Server()
{
}

void Server::run()
{
	bool done = false;

	while (!done)
	{
		if (this->selector.wait(sf::seconds(1))) {
			if (this->selector.isReady(this->listener)) {
				sf::TcpSocket *socket = new sf::TcpSocket;
				this->listener.accept(*socket);
				sf::Packet packet;
				std::string id;
				if (socket->receive(packet) == sf::Socket::Done)
					packet << id;

				std::cout << id << " has connected to chat " << std::endl;
				clients.push_back(socket);
				this->selector.add(*socket);
			}
			else {
				for (int i = 0; i < clients.size(); i++)
				{
					if (this->selector.isReady(*clients[i]))
					{
						sf::Packet packet, sendPacket;
						if (clients[i]->receive(packet) == sf::Socket::Done)
						{
							std::string text;
							packet >> text;
							sendPacket << text;
							for (int j = 0; j < clients.size(); j++)
							{
								if (i != j)
								{
									clients[j]->send(sendPacket);
								}
							}
						}
					}
				}
			}
		}
	}

	for (std::vector<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); it++)
		delete *it;
}
