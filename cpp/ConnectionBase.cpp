#include "stdafx.h"
#include "ConnectionBase.h"



//��ʼ���б�ԭ���ܷ��ڳ�ʼ���б�Ķ�ţ�ֻ�ܳ�ʼ�����ܸ�ֵ�ı����
ConnectionBase::ConnectionBase ( boost::shared_ptr<boost::asio::io_service> io_service_ptr )
    : socket_ ( *io_service_ptr ), strand_ ( *io_service_ptr )
{
    //һ��io_service_ptr ���� connection
    //��ʼ����Աsocket strand(strand���У�io_service����)
}

ConnectionBase::~ConnectionBase( )
{
    //������������Ϊ�˽��������һ�����⣺�����ָ��ָ����������󣬲��û����ָ��ɾ�����������
}

boost::asio::ip::tcp::socket& ConnectionBase::socket()
{
    return socket_;
}

