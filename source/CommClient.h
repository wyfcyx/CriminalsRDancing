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
class Game;

typedef boost::shared_ptr<CommClient> ClientPtr;

class CommClient: public boost::enable_shared_from_this<CommClient>, boost::noncopyable {
public:
	typedef CommClient self_type;
	CommClient(io_service &service);
	static boost::shared_ptr<CommClient> SmartNew(io_service &service);

	ip::tcp::socket pipe_socket_;

	void AfterConnect(std::vector<ClientPtr> *client_list);

	void AsyncRead();
	void AfterRead(const error_code &err, size_t bytes);

	void AsyncWrite(const std::string &message);
	void AfterWrite(const error_code &err, size_t bytes);

	size_t IsComplete(const error_code &err, size_t bytes);

private:
	char read_buffer_[MAX_BUFFER];
	char write_buffer_[MAX_BUFFER];

	int player_id_;
};

#endif // _COMM_CLIENT_H_

