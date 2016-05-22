#ifndef _COMM_CLIENT_H_
#define _COMM_CLIENT_H_

#include <array>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "defs.h"

using namespace boost::asio;

typedef boost::shared_ptr<CommClient> ClientPtr;

class CommClient: public boost::enable_shared_from_this<CommClient>, boost::noncopyable {
public:
	CommClient(): service_(), pipe_socket_(service_);
	shared_ptr<CommClient> SmartNew();

private:
	ip::tcp::pipe_socket_;
	io_service service_;
	char read_buffer_[MAX_BUFFER];
	char write_buffer_[MAX_BUFFER];

	static std::vector<CommClient> client_list;
}

#endif // _COMM_CLIENT_H_
