#include "stdafx.h"

#include "server.h"

using namespace std;

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

inline void EnableMemLeakCheck()
{
    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_DELAY_FREE_MEM_DF | _CRTDBG_CHECK_EVERY_1024_DF | _CRTDBG_CHECK_CRT_DF /*| _CRTDBG_REPORT_FLAG */ );
    _CrtSetReportMode ( _CRT_WARN, _CRTDBG_MODE_DEBUG | _CRTDBG_MODE_WNDW );
}

// �������Ч�汾�����������ַ������Ƶ�version�У�
// ��������Ч�汾��versionΪ�ա�
void CheckVersion ( const char* param, std::string* version )
{
    if ( !strcmp ( param, "-d" ) )
    {
        *version = "Demo";
    }
    
    else if ( !strcmp ( param, "-s" ) )
    {
        *version = "Study";
    }
    
    else if ( !strcmp ( param, "-t" ) )
    {
        *version = "Training";
    }
}

// Usage:server -d nw;
// server -s south;
// server -t north;


static void help()
{

}
int main ( int ac, char *av[] )
{
    /* if ( ac <= 2 )
     {
         cout << "Usage:server [-version] [-drill]" << endl;
         return 0;
     }
    
     std::string* version = new std::string;
     CheckVersion ( av[1], version );
    
     if ( version->empty() )
     {
         cout << av[1] << "������Ч�Ĳ���" << endl;
         return 0;
     }*/
    
    //	EnableMemLeakCheck();
    /*
    boost::asio::io_service bootp_service;
    BootstrapServer bootp_server(bootp_service);
    if (*version == "Training") {
      // The run() function blocks until all work has finished
      // and there are no more handlers to be dispatched
      // or until the io_service has been stopped.
      boost::thread t(boost::bind(&boost::asio::io_service::run, &bootp_service));
    
    }*/
    //path ������������·����������Ŀ¼
    std::string path ( av[0] );
    //rfind find reverse �������
    path = path.substr ( 0, path.rfind ( "\\" ) + 1 );//ֻ����Ŀ¼���֣�������.exe������
    cout << path << endl;
    boost::shared_ptr<DServer> server_ptr ( new DServer() );
    //server_ptr->init ( path, *version, av[2] );
    server_ptr->init ( path, "Demo", "north" );
    server_ptr->start_service();
    
    return 0;
}