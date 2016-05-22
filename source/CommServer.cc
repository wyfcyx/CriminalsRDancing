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

void CommServer :: Connect(ip::tcp::endpoint server, void (UserInterface :: *FailedHandler)(), UserInterface *from)
{
	(from->*FailedHandler)();
}
