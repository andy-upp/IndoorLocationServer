/************************************************************************/
/* ConnectionBase.h
 * boost asio socket ͨ�Ż��࣬ʵ�����첽�շ���Ϣ
/************************************************************************/


#ifndef __CONNECTION_BASE_H__
#define __CONNECTION_BASE_H__

#pragma once

#include "stdafx.h"
#include "codec.h"


class ConnectionBase
{
    public:

        ConnectionBase ( boost::shared_ptr<boost::asio::io_service> io_service_ptr );

        //��������������
        virtual ~ConnectionBase();

        boost::asio::ip::tcp::socket& socket();

        //д��t���ܱ�
        template <typename T, typename Handler>
        void async_write ( const T &t, Handler handler );

        //������ľ���t
        template <typename T, typename Handler>
        void async_read ( T &t, Handler handler );


        template <typename T, typename Handler>
        void handle_read_header ( const boost::system::error_code& e,
                                  T &t, boost::tuple<Handler> handler );


        template <typename T, typename Handler>
        void handle_read_data ( const boost::system::error_code& e,
                                T &t, boost::tuple<Handler> handler );


        //������#define
        enum { header_length = 4, type_length = 4 };

        //socket_ͨ����
        boost::asio::ip::tcp::socket socket_;
        //strand_ wrap�ã�����
        boost::asio::strand strand_;

        std::string outbound_header_;
        std::vector<Byte> outbound_data_;

        //���ݰ�ͷ�����������ݲ��䳤
        std::vector<Byte> inbound_header_;
        // Byte inbound_header_[header_length];
        char inbound_type_[type_length];
        std::vector<Byte> inbound_data_;

};



template<typename T, typename Handler>
void ConnectionBase::async_write ( const T &t, Handler handler )
{
    outbound_data_ = EncodeAsByteArray ( t );
    std::vector<boost::asio::const_buffer> buffers;
    buffers.push_back ( boost::asio::buffer ( outbound_data_ ) );
    boost::asio::async_write ( socket_, buffers, handler );
}


/************************************************************************/
/* asyn_read consist of read_header and read_data               */
/************************************************************************/

template <typename T, typename Handler>
void ConnectionBase::async_read ( T &t, Handler handler )
{
    //����ָ�� ConnectionBase::*f ��ConnectionBase::���Բ�Ҫ�ɣ����������f�ĵط���handle_read_header
    //tuple   �ܶ��ʱ�����Ǿ�����ҪΪ���ǵĺ������ض��ֵ std::pair��ʵ����boost::tuple��2����������������boost::tuple����԰󶨸���Ĳ�������������Ե���ʵ�����޶���������
    void ( ConnectionBase::*f ) ( const boost::system::error_code&, T&, boost::tuple<Handler> ) = &ConnectionBase::handle_read_header<T, Handler>;
    inbound_header_.clear();
    inbound_header_.resize ( header_length );
    boost::asio::async_read ( socket_,
                              boost::asio::buffer ( inbound_header_ ),
                              boost::bind ( f,
                                            this,
                                            boost::asio::placeholders::error,
                                            boost::ref ( t ),
                                            boost::make_tuple ( handler ) ) );
}

template <typename T, typename Handler>
void ConnectionBase::handle_read_header ( const boost::system::error_code& e,
        T &t, boost::tuple<Handler> handler )
{
    if ( e )
    {
        boost::get<0> ( handler ) ( e );
    }
    else
    {
        std::istringstream is ( std::string ( inbound_header_.begin(), inbound_header_.end() ) );
        std::size_t inbound_data_size = 0;
        //��Ϣͷ������СΪ20
        if ( ! ( is >> std::hex >>  inbound_data_size ) )
        {
            boost::system::error_code error ( boost::asio::error::invalid_argument );
            boost::get<0> ( handler ) ( error );
            return;
        }
        if ( inbound_data_size < 20 )
        {

            return;
        }


        inbound_data_.resize ( inbound_data_size );
        void ( ConnectionBase::*f ) ( const boost::system::error_code&, T&, boost::tuple<Handler> ) = &ConnectionBase::handle_read_data<T, Handler>;
        boost::asio::async_read ( socket_,
                                  boost::asio::buffer ( inbound_data_ ),
                                  boost::bind ( f,
                                                this,
                                                boost::asio::placeholders::error,
                                                boost::ref ( t ),
                                                handler ) );
    }
}

template <typename T, typename Handler>
void ConnectionBase::handle_read_data ( const boost::system::error_code& e,
                                        T &t, boost::tuple<Handler> handler )
{
    if ( e )
    {
        boost::get<0> ( handler ) ( e );
    }
    else
    {
        try
        {
            t = decode ( inbound_data_ );
        }
        catch ( std::exception& e )
        {
            boost::system::error_code error ( boost::asio::error::invalid_argument );
            boost::get<0> ( handler ) ( error );
            return;
        }

        boost::get<0> ( handler ) ( e );
    }
}

#endif