#include <cstdio>
#include <cstring>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include "CommServer.h"
#include "UserInterface.h"

using namespace boost::asio;

CommServer :: CommServer(UserInterface *user): service_(), pipe_socket_(service_),
	user_(user)
{
}

boost::shared_ptr<CommServer> CommServer :: SmartNew(UserInterface *user)
{
	boost::shared_ptr<CommServer> re(new CommServer(user));
	return re;
}

void CommServer :: Connect(ip::tcp::endpoint server)
{
	pipe_socket_.async_connect(server, MEM_FN1(AfterConnect, _1));
}

void CommServer :: AfterConnect(const error_code &err)
{
	if (err)
		user_->FailedToConnect();
	else
		user_->SuccessToConnect();
}

void CommServer :: Disconnect()
{
	if (!pipe_socket_.is_open())
		return ;
	pipe_socket_.close();
	user_->Entrance();
}

size_t CommServer :: IsComplete(const error_code &err, size_t bytes)
{
	if (err)	return 0;
	bool found = std::find(read_buffer_, read_buffer_ + bytes, '\n') < read_buffer_ + bytes;

	return found ? 0 : 1;
}

void CommServer :: AsyncRead()
{
	async_read(pipe_socket_, buffer(read_buffer_), MEM_FN2(IsComplete, _1, _2),
			MEM_FN2(AfterRead, _1, _2));
}

void CommServer :: AfterRead(const error_code &err, size_t bytes)
{
	if (err)	return ;
	std::string message(read_buffer_, bytes);
	user_->Receive(message);
}

void CommServer :: AsyncWrite(const std::string &message)
{
	std::string will_send = message + '\n';
	std::copy(will_send.begin(), will_send.end(), write_buffer_);
	pipe_socket_.async_write_some(buffer(write_buffer_, will_send.size()), MEM_FN2(AfterWrite, _1, _2));
}

void CommServer :: AfterWrite(const error_code &err, size_t bytes)
{
	AsyncRead();
}
