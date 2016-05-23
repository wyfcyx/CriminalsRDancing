#include <cstdio>
#include <cstring>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include "defs.h"
#include "CommClient.h"

using namespace boost::asio;

io_service service;

void NextAccept(boost::shared_ptr<CommClient> client, const error_code &err, ip::tcp::acceptor *acceptor)
{
	client->AfterConnect();

	boost::shared_ptr<CommClient> next_client = CommClient::SmartNew(service);
	acceptor->async_accept(next_client->pipe_socket_, boost::bind(NextAccept, next_client, _1, acceptor));
}

int main()
{
	ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), DEFAULT_PORT));

	boost::shared_ptr<CommClient> client = CommClient::SmartNew(service);
	acceptor.async_accept(client->pipe_socket_, boost::bind(NextAccept, client, _1, &acceptor));

	service.run();

	return EXIT_SUCCESS;
}

