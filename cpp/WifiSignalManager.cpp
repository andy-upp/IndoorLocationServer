#include "stdafx.h"
#include "WifiSignalManager.h"
#include "message.h"
#include "InternalMessage.h"

#include "ObjectManager.h"

#include "wifi.hxx"
#include "EntityMessageAdapter.h"
#include "wifi-odb.hxx"



WifiSignalManager::WifiSignalManager ( void )
{
}



bool WifiSignalManager::onMsgAdd ( boost::shared_ptr<InternalMessage> in_msg )
{
    //���ź�������5���Ӹ���һ�����ݿ⣬û�еĻ��򲻸��¡��ڸ������ݿ�֮ǰ�������Ч������̫���򲻸��£��������ڰ�

    boost::shared_ptr<vrmsg::AddWifiSignalRequest> msg = boost::dynamic_pointer_cast<vrmsg::AddWifiSignalRequest> ( in_msg->message );
    
    for ( int i = 0; i < msg->signals().size(); ++i )
    {
        boost::shared_ptr<WifiRaw> signal ( EntityMessageAdapter::toWifiRaw ( msg->signals ( i ) ) ) ;
        unsigned long id = CObjectManager<WifiRaw>::getInstance()->persist ( signal );
        boost::shared_ptr<WifiSample> sample ( new WifiSample ( id ) );
        CObjectManager<WifiSample>::getInstance()->add ( sample );
    }
    
    return true;
}

WifiSignalManager::~WifiSignalManager()
{

}


