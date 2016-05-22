#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include "defs.h"
#include "UserInterface.h"
#include "CommServer.h"
#include "Player.h"

using namespace boost::asio;

#define VERSION "V0.02"

UserInterface :: UserInterface()
{
	server_ip_ = "127.0.0.1";
	port_ = DEFAULT_PORT;
	pipe_ = boost::shared_ptr<CommServer>(new CommServer);
	username_ = "noname";
}

void UserInterface :: Welcome()
{
	std::cout << "Welcome to CriminalsRDancing " << VERSION << std::endl;
	Entrance();
}

void UserInterface :: FailedToConnect()
{
	std::cout << "Failed to connect the server " << server_ip_ << ':' << port_ << std::endl;
	Entrance();
}

void UserInterface :: SuccessToConnect()
{
	std::cout << "Succeeded to connect the server " << server_ip_ << ':' << port_ << std::endl;
	SquareView();
}

void UserInterface :: SquareEntrance()
{
	while (true) {
		std::cout << "Now you are in the square." << std::endl;
		std::cout << "Current status:" << std::endl;
		std::cout << "Username: " << (username_.length() ? username_ : "(empty)") << std::endl;
		std::cout << "Server IP: " << (server_ip_.length() ? server_ip_ : "(empty)") << std::endl;
		std::cout << "Server port: " << port_ << std::endl;

		std::cout << "Commands:" << std::endl;
		std::cout << "\'quit\', \'q\': Quit this server." << std::endl;
		static std::string s;
		std::cin >> s;
		if (s == "quit" || s == 'q') {
			pipe_->Disconnect(this);
			return ;
		}
	}
}

void UserInterface :: Entrance()
{
	while (true) {
		puts("Commands:");
		puts("\'version\', \'v\':\t\tView the current version of the game.");
		puts("\'name\', \'n\':\t\tInput or change your name in the game. (Max 20 characters)");
		puts("\'server\', \'s\':\t\tSet or change server ip.");
		puts("\'port\', \'p\':\t\tSet or change server port. (Default 8346)");
		puts("\'connect\', \'c\':\t\tConnect to the server.");
		puts("\'quit\', \'q\':\t\tQuit the game.");

		static std::string s;
		std::cin >> s;
		if (s == "version" || s == "v") {
			std::cout << VERSION << std::endl;
		}
		else if (s == "quit" || s == "q") {
			return ;
		}
		else if (s == "name" || s == "n") {
			std::cin >> username_;
		}
		else if (s == "server" || s == "s") {
			std::cin >> server_ip_;
		}
		else if (s == "port" || s == "p") {
			int _storage = port_;
			std::cin >> port_;
			if(port_ <= 1024 || port_ >= 65535)
				port_ = _storage;
		}
		else if (s == "connect" || s == "c") {
			if (!username_.length()) {
				puts("No username. Please enter your username.");
				continue;
			}
			if (!server_ip_.length()) {
				puts("No server ip. Please enter the ip address of the server.");
				continue;
			}

			// attempt to connect to server
			ip::tcp::endpoint server(ip::address::from_string(server_ip_), port_);
			pipe_->Connect(server, &UserInterface::FailedToConnect, this);
		}
		else {
			printf("unknown command.\n");
		}
	}



	// TODO: get player data from server
	// TODO: create a player using the data from server

	return ;
}

