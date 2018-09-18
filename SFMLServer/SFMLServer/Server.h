#pragma once
#include "stdafx.h"

class Server
{
private:
	sf::TcpListener listener;
	sf::SocketSelector selector;
public:
	std::vector<sf::TcpSocket*> clients;
	Server(int port);
	~Server();
	void run();
};