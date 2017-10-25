/********************************************************************
	Author:		Wang Yu
	Created:	2013/09/04
	Revised:	2013/09/04   13:58

	Purpose:	�ͻ�������������
            �����㲥���ݰ����Կͻ�������������Ӧ��ʹ�ͻ����ܹ�̽�⵽����ˡ�
*********************************************************************/

#ifndef BOOTSTRAP_SERVER_H_
#define BOOTSTRAP_SERVER_H_

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>

namespace ip = boost::asio::ip;

class BootstrapServer
{
    public:
        BootstrapServer ( boost::asio::io_service& io_service );
        void start_service();
        void stop_service();
        void handle_receive ( const boost::system::error_code& error, std::size_t bytes_transferred );
        void handle_send (
            boost::shared_ptr<std::string> /*message*/,
            const boost::system::error_code& /*error*/,
            std::size_t /*bytes_transferred*/ );

    private:
        ip::udp::socket socket_;
        ip::udp::endpoint remote_endpoint_;
        boost::array<char, 32> recv_buffer_;
};

#endif