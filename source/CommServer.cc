#include <cstdio>
#include <cstring>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

#include "CommServer.h"

using namespace boost::asio;

CommServer :: CommServer(): service_(), pipe_socket_(service_)
{
}

boost::shared_ptr<CommServer> CommServer :: SmartNew()
{
	boost::shared_ptr<CommServer> re(new CommServer());
	return re;
}

void CommServer :: Connect(ip::tcp::endpoint server, UserInterface *from)
{
	pipe_socket_.async_connect(server, MEM_FN1(AfterConnect, _1, from));
}

void CommServer :: AfterConnect(error_code &err, UserInterface *from)
{
	if (err)
		from->FailedToConnect();
	else
		from->SuccessToConnect();
}

void CommServer :: Disconnect(UserInterface *from)
{
	if (!pipe_socket_.is_open())
		return ;
	pipe_socket_.close();
	from->Entrance();
}
