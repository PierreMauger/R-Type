#ifndef NETCOMMON_HPP_
#define NETCOMMON_HPP_

#include <deque>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "Queue.hpp"
#include "Connection.hpp"

#define _NET_BUFFER_SIZE 2048

typedef boost::array<uint8_t, _NET_BUFFER_SIZE>         _STORAGE_DATA;
typedef Queue<_STORAGE_DATA>                            _QUEUE_TYPE;
typedef boost::asio::ip::udp                            _B_ASIO_UDP;
typedef boost::asio::ip::tcp                            _B_ASIO_TCP;

#endif /* !NETCOMMON_HPP_ */