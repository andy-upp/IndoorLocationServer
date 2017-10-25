/************************************************************************/
/*    ͨ�Ź����ߣ�Ӧ�ò�ͨ�ŵĸ߲�
 *                                                                      */
/************************************************************************/

#ifndef __ConnectionManager_H__
#define __ConnectionManager_H__


#include "stdafx.h"
//#include "message.h"


class ConnectionServer;
class DServer;

using namespace google;

class ConnectionManager : public boost::enable_shared_from_this<ConnectionManager>
{
    public:
        ConnectionManager ( boost::shared_ptr<DServer> s_ptr );

        void output_error ( std::string err_msg, const boost::system::error_code &e );

        void start_accept();
        void handle_accept ( const boost::system::error_code& error, boost::shared_ptr<ConnectionServer> client_ptr );

        //ordered broadcast, unicast
        //conn_id,before select role
        //role_id, after select role
        //default by role_id, entities��������Ϣһ��role_id, ��broadcast
        // ����
        void unicast_by_role_id ( std::string role_id, boost::shared_ptr<protobuf::Message> msg );
        void unicast_by_conn_id ( std::string conn_id, boost::shared_ptr<protobuf::Message> msg );
        void unicast_to_ui ( boost::shared_ptr<protobuf::Message> msg );
        void unicast_msgs ( std::string role_id, std::vector<boost::shared_ptr<protobuf::Message>> msgs );
        void unicast_msgs_by_conn_id ( std::string conn_id, std::vector<boost::shared_ptr<protobuf::Message>> msgs );


        //�㲥
        void broadcast ( boost::shared_ptr<protobuf::Message> msg );
        void broadcast_msgs ( std::vector<protobuf::Message> msgs );

        void broadcast_except_by_role_id ( boost::shared_ptr<protobuf::Message> msg, std::string role_id );
        void broadcast_except_by_conn_id ( boost::shared_ptr<protobuf::Message> msg, std::string conn_id );
        void broadcast_msgs_except ( std::vector<protobuf::Message> msgs, std::string role_id );
        void broadcast_msgs_except_by_conn_id ( std::vector<protobuf::Message> msgs, std::string conn_id );

        void handle_timeout ( std::string role_id );

        // ����ͻ��˵ĵĵ�¼����
        // ���������棬�򽫵�¼�����͵�UI������֤
        // ���������汾����ֱ�Ӹ�֪�ͻ��˵�¼�ɹ�
        void handle_login ( const boost::shared_ptr<protobuf::Message> msg );

        // ����UI�Կͻ��˵���֤
        // ����֤�����֪�ͻ��ˣ��ɹ�/ʧ�ܣ�
        // ���ɹ��򱣳����ӣ���ʧ����Ͽ����Ӳ���connection_���Ƴ�
        void handle_verify ( const boost::shared_ptr<protobuf::Message> msg );

        void del_conn ( std::string conn_id );
        void del_conn ( boost::shared_ptr<ConnectionServer> conn );
        //private:

        std::vector<boost::shared_ptr<ConnectionServer>> connections_;
        boost::mutex connections_mutex;

        //accept conn
        std::map<std::string, boost::weak_ptr<ConnectionServer>> conn_id_map;//conn_id -> conn_ptr;
        boost::mutex conn_id_map_mutex;

        boost::weak_ptr<DServer> server_ptr;
        boost::shared_ptr<ConnectionServer> temp_conn;
        boost::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor_ptr;

        std::string ui_conn_id_;

        //connections_ ���ӵļ���
        //conn_id_map �������ʲô������<map��������Ч�ʿ��ǣ����Ҹ���>


};

#endif