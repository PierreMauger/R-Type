#include "client.hpp"
#include "common.hpp"
#include "message.hpp"

//$----------- Constructors and destructors ------------$//

template <typename T> net::client<T>::client()
{
    this->_tcpSocket = asio::ip::tcp::socket(this->_asioContext);
    this->_udpSocket = asio::ip::udp::socket(this->_asioContext);
}

template <typename T> net::client<T>::~client()
{
    Disconnect();
}

template <typename T> bool net::client<T>::Connect(const std::string &host, const uint16_t port)
{
    try {
        this->_connection = std::make_unique<connection<T>>();

        asio::ip::tcp::resolver resolver(this->_asioContext);

    } catch(std::exception &error) {
        std::cerr << "Client Exception: " << error.what() << std::endl;
        return false;
    }
    return true;
}

template <typename T> void net::client<T>::Disconnect()
{
    if (IsConnected())
        this->_connection->Disconnect();
    this->_asioContext.stop();
    if (this->_threadContext.joinable())
        this->_threadContext.join();
    this->_connection.release();
}

template <typename T> bool net::client<T>::IsConnected()
{
    if (this->_connection)
        return this->_connection->IsConnected();
    return false;
}

template <typename T> net::queue<net::owned_message<T>> &net::client<T>::GetQueueIn()
{
    return this->_queueMessagesIn;
}