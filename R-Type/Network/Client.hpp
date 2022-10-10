#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include "NetCommon.hpp"
#include "Connection.hpp"

class Client {
    private:
        void handleMsgUdp(const boost::system::error_code &error, _STORAGE_DATA buffer, size_t size, _B_ASIO_UDP::endpoint newEndpoint);

    protected:
        boost::asio::io_context &_ioContext;
        _B_ASIO_TCP::resolver _resolver;
        _B_ASIO_UDP::socket _udpSocket;
        boost::shared_ptr<Connection> _connection;
        _QUEUE_TYPE _dataIn;

    public:
        Client(boost::asio::io_context &ioContext, std::string ip, uint16_t portUdp, uint16_t portTcp);
        ~Client();

        void initClient();

        void open();
        void close();

        void tcpMsg(_STORAGE_DATA data);
        void udpMsg(_STORAGE_DATA data);

        virtual void updateAction();
};

#endif /* !CLIENT_HPP_ */