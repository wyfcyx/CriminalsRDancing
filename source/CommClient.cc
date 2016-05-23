#include <cstdio>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "defs.h"
#include "CommClient.h"

using namespace boost::asio;

CommClient :: CommClient(io_service &service): pipe_socket_(service)
{
}

boost::shared_ptr<CommClient> CommClient :: SmartNew(io_service &service)
{
	boost::shared_ptr<CommClient> re(new CommClient(service));
	return re;
}

void CommClient :: AfterConnect()
{
	AsyncRead();
}

void CommClient :: AsyncRead()
{
	async_read(pipe_socket_, buffer(read_buffer_), boost::bind(&CommClient::IsComplete, shared_from_this(), _1, _2),
			boost::bind(&CommClient::AfterRead, shared_from_this(), _1, _2));
			//MEM_FN2(IsComplete, _1, _2), MEM_FN2(AfterRead, _1, _2));
}

void CommClient :: AfterRead(const error_code &err, size_t bytes)
{
	if (err)	return ;
	std::string message(read_buffer_, bytes);

	// return message;
}

void CommClient :: AsyncWrite(const std::string &message)
{
	std::copy(message.begin(), message.end(), write_buffer_);
	pipe_socket_.async_write_some(buffer(write_buffer_, message.size()),
			MEM_FN2(AfterWrite, _1, _2));
}

void CommClient :: AfterWrite(const error_code &err, size_t bytes)
{
	AsyncRead();
}

size_t CommClient :: IsComplete(const error_code &err, size_t bytes)
{
	if (err)	return 0;

	bool found = std::find(read_buffer_, read_buffer_ + bytes, '\n') < read_buffer_ + bytes;
	return found ? 0 : 1;
}

