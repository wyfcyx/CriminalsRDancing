#ifndef _COMM_SERVER_H_
#define _COMM_SERVER_H_

#include <array>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include "defs.h"

class UserInterface;
class CommServer;

using namespace boost::asio;

typedef CommServer self_type;

class CommServer: public boost::enable_shared_from_this<CommServer>, boost::noncopyable {
public:
	CommServer(UserInterface *user);
	boost::shared_ptr<CommServer> SmartNew(UserInterface *user);

	void Connect(ip::tcp::endpoint server);
	void Disconnect();

	void AsyncWrite(const std::string &message);
	size_t IsComplete(const error_code &err, size_t bytes);
	void AfterRead(const error_code &err, size_t bytes);
	void AfterWrite(const error_code &err, size_t bytes);
	void AfterConnect(const error_code &err);

private:
	io_service service_;
	ip::tcp::socket pipe_socket_;
	UserInterface *user_;
#define MAX_BUFFER 1024
	char read_buffer_[MAX_BUFFER];
	char write_buffer_[MAX_BUFFER];

	void AsyncRead();
};

#endif // __COMM_SERVER_H_
