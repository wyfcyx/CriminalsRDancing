#include <cstdio>
#include <cstring>
#include <iostream>

#include <boost/shared_ptr.hpp>

#include "defs.h"
#include "ServerController.h"

using namespace boost::asio;

ServerController :: ServerController(): acceptor_(service, ip::tcp::endpoint(ip::tcp::v4(), DEFAULT_PORT));
{
	ClientPtr client = CommClient::SmartNew(service_);
	acceptor.async_accept(client->pipe_socket_, boost::bind(Accept, client, _1));

	service_.run();
}

void ServerController :: Accept(ClientPtr client, const error_code &err)
{
	client->AfterConnect(client_list_);

	ClientPtr next_client = CommClient::SmartNew(service_);
	acceptor_->async_accept(next_client->pipe_socket_, boost::bind(&ServerController::Accept, next_client, _1));
}

void DisconnectServer(ClientPtr client)
{
	std::vector<ClientPtr>::iterator iter = std::find(client_list_.begin(), client_list_.end(), client);
	if (client->status_) {
		// TODO: tell RoomController to disconnect client.
	}
	client_list_.erase(iter);
}

void GetInRoom(ClientPtr client, int room)
{
	client->status_ = room;
	++room_count_[room];
}

void GetOutRoom(ClientPtr client)
{
	--room_count[client->status_];
	client->status_ = 0;
}
