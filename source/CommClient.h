#ifndef _COMM_CLIENT_H_
#define _COMM_CLIENT_H_

#include <array>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "defs.h"

using namespace boost::asio;

class CommClient;

typedef boost::shared_ptr<CommClient> ClientPtr;

io_service service;

class CommClient: public boost::enable_shared_from_this<CommClient>, boost::noncopyable {
public:
	typedef CommClient self_type;
	CommClient();
	static boost::shared_ptr<CommClient> SmartNew();

	ip::tcp::socket pipe_socket_;

	void AfterConnect();

	void AsyncRead();
	void AfterRead(const error_code &err, size_t bytes);

	void AsyncWrite(const std::string &message);
	void AfterWrite(const error_code &err, size_t bytes);

	size_t IsComplete(const error_code &err, size_t bytes);

private:
	char read_buffer_[MAX_BUFFER];
	char write_buffer_[MAX_BUFFER];

	static std::vector<ClientPtr> client_list;
};

#endif // _COMM_CLIENT_H_
