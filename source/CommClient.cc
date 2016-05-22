#include <cstdio>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "defs.h"
#include "CommServer.h"

CommClient :: CommClient(): service_(), pipe_socket_(service_)
{
}

shared_ptr<CommClient> SmartNew()
{
	shared_ptr<CommClient> re(new CommClient());
	return re;
}

