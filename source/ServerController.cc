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
	client->AfterConnect();

	ClientPtr next_client = CommClient::SmartNew(service_);
	acceptor_->async_accept(next_client->pipe_socket_, boost::bind(&ServerController::Accept, next_client, _1));
}
