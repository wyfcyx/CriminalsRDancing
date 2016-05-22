#ifndef _COMM_SERVER_H_
#define _COMM_SERVER_H_

#include <array>

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include "defs.h"

class UserInterface;

using namespace boost::asio;

class CommServer: public boost::enable_shared_from_this<CommServer>, boost::noncopyable {
public:
	typedef CommServer self_type;
	CommServer();
	boost::shared_ptr<CommServer> SmartNew();

	void Connect(ip::tcp::endpoint server, void (UserInterface :: *FailedHandler)(), UserInterface *from);
private:
	io_service service_;
	ip::tcp::socket pipe_socket_;


};

#endif // __COMM_SERVER_H_
