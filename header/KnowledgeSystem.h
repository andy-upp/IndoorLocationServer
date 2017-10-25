/************************************************************************/
/*
        ֪ʶϵͳ����ѵ���Ͷ�λ������
        ���ڲ�ͬ���ƶ��豸��ȡ����wifi����ǿ�Ȳ�ͬ�����Զ������������е�λ������
        ����ͬ���豸�ɼ��������ݺϲ���һ��
        ���ǣ���һ��������ʧȥ�˾���Զ����Ϣ����Զ�����ź������ͽ������ź���������
        ����Ϊ���޸�����ǿ�Ȳ�ͬ������Ա�����ͬ��������ͨcosine�㷨����Ϊ��������
        ������������
        ���Ҫ���ǵ����룬���ܶ��������е�λ�������Ľ���consine�㷨����ͨ
        consine�����ϳ��������������ȱ�ֵ����
*/
/************************************************************************/

#ifndef __KNOWLEDGE_SYSTEM_H__
#define __KNOWLEDGE_SYSTEM_H__

#pragma once
#include "stdafx.h"
#include "wifi.hxx"
#include "wifi-odb.hxx"

class DServer;
class InternalMessage;




class KnowledgeSystem : public boost::enable_shared_from_this<KnowledgeSystem>
{
        typedef std::vector<std::vector<int>> array2_type;
    public:
    
        KnowledgeSystem ( boost::shared_ptr<DServer> svr_ptr );
        ~KnowledgeSystem ( void );
        
        
        
        void init();
        boost::weak_ptr<DServer> server_ptr;
        void test();
        void onQueryPosition ( boost::shared_ptr<InternalMessage> msg );
        template<typename T>
        double Consine ( const std::vector<T> &vec_q, const std::vector<T> &vec_d );
        //deprecated
        template<typename T>
        double Consine (  std::map<std::string, T> &map_q,  std::map<std::string, T> &map_d );
        
        template<typename T>
        double Average ( const std::vector<T> &vec );
        template<typename T>
        double Variance ( const std::vector<T> &vec );
        template<typename T>
        double StandDeviation ( const std::vector<T> &vec );
        template<typename T>
        double SubConsine ( const std::vector<T> &vec_q, const std::vector<T> &vec_d );
        template<typename T>
        double IConsine ( const std::vector<T> &vec_q, const std::vector<T> &vec_d );
        //deprecated
        template<typename T>
        double IConsine ( std::map<std::string, T> &map_q,  std::map<std::string, T> &map_d  );
        template<typename T>
        int CountCommonAp ( std::map<std::string, T> &map_q,  std::map<std::string, T> &map_d  );
        
        template<typename T>
        double Similarity ( std::map<std::string, T> &map_q,  std::map<std::string, T> &map_d );
        
        // double Consine ( std::map<std::string, double> &map_q,  std::map<std::string, double> &map_d );
        template<typename T>
        double DotProduct ( const std::vector<T> &vec_q, const std::vector<T> &vec_d );
        template<typename T>
        double Distance_Euclid ( const std::vector<T> &vec_q, const std::vector<T> &vec_d );
        template<typename T>
        double Distance_Manhat ( const std::vector<T> &vec_q, const std::vector<T> &vec_d );
        template <typename T>
        double Norm2 ( const std::vector<T> &vec );
        template<typename T>
        void normalize ( std::vector<T> &vec );
        //��λ��ÿ���豸��wifi�����������豸������
        template<typename T>
        void normalize ( std::map<std::string, T> &val );
        //��һ��wifi��������ap���з��˲��õ�һ������
        template <typename T>
        double IAverage ( const std::vector<T> &vec );
        template <typename T>
        double Median ( std::vector<T> &vec );
        int ProcessRawData2 ( const std::string pos, boost::shared_ptr<std::vector<WifiRaw>> raw_vec );
        void ProcessRawData ();
        void showWifiData();
        void OnlineTraining();
    private:
        boost::shared_ptr<std::vector<WifiData>> p_res;
};

template <typename T>
double KnowledgeSystem::Median ( std::vector<T> &vec )
{
    int size = vec.size();
    
    if ( size < 1 ) return 0;
    
    if ( size == 1 ) return vec[0];
    
    T median_l = nth_element ( vec.begin(), vec.begin() + size / 2, vec.end() );
    
    if ( size % 2 == 1 )
    {
        return vec[size / 2];
    }
    else
    {
        T median_r = nth_element ( vec.begin(), vec.begin() + size / 2 + 1, vec.end() );
        return ( median_l + median_r ) / 2.0;
    }
}

template<typename T>
double KnowledgeSystem::StandDeviation ( const std::vector<T> &vec )
{
    return sqrt ( Variance ( vec ) );
}

template<typename T>
double KnowledgeSystem::Average ( const std::vector<T> &vec )
{
    double ret = 0;
    int size = vec.size();
    
    for ( int i = 0; i < size; ++i )
    {
        ret += vec[i];
    }
    
    return ret / size;
}

template<typename T>
double KnowledgeSystem::Variance ( const std::vector<T> &vec )
{
    double avg = Average ( vec );
    double ret = 0;
    int size = vec.size();
    double temp = 0;
    
    for ( int i = 0; i < size; ++i )
    {
        temp = vec[i] - avg;
        ret += temp * temp;
    }
    
    return ret / size;
}


template<typename T>
double KnowledgeSystem::Distance_Manhat ( const std::vector<T> &vec_q, const std::vector<T> &vec_d )
{
    if ( vec_q.size() != vec_d.size() ) return 0;
    
    double ret = 0;
    
    for ( int i = 0; i < vec_d.size(); ++i )
    {
        //���ϲ�ľ���ֵ
        ret += abs ( vec_d[i] - vec_q[i] );
    }
    
    return ret;
}

//Ŀǰû�кõİ취ȷ���ĸ������Ǹ��ţ�ֻ��ͨ���������д�һ����������cos
template<typename T>
double KnowledgeSystem::SubConsine ( const std::vector<T> &vec_q, const std::vector<T> &vec_d )
{
    if ( vec_q.size() != vec_d.size() ) return 0;
    
    int size = vec_q.size();
    std::vector<double> vec_cos;
    std::vector<T> sub_q ( vec_q.begin(), vec_q.end() - 1 );
    std::vector<T> sub_d ( vec_d.begin(), vec_d.end() - 1 );
    
    
    double cos = Consine ( sub_q, sub_d );
    vec_cos.push_back ( cos );
    cout << cos << endl;
    
    for ( int i = 0; i < size - 1; i++ )
    {
        sub_q[i] = vec_q[ ( size - 1 + i ) % size];
        sub_d[i] = vec_d[ ( size - 1 + i ) % size];
        cos = Consine ( sub_q, sub_d );
        cout << cos << endl;
        vec_cos.push_back ( cos );
    }
    
    std::vector<double>::iterator it_max =  std::max_element ( vec_cos.begin(), vec_cos.end() );
    return *it_max;
}

template<typename T>
double KnowledgeSystem::Similarity ( std::map<std::string, T> &map_q, std::map<std::string, T> &map_d )
{
    std::vector<T> query_vec;
    std::vector<T> data_vec;
    
    for ( typename std::map<std::string, T>::iterator it = map_q.begin(); it != map_q.end(); ++it )
    {
        typename std::map<std::string, T>::iterator jt = map_d.find ( it->first ) ;
        
        if ( jt != map_d.end() )
        {
            query_vec.push_back ( it->second );
            data_vec.push_back ( jt->second );
            //cout << it->first << "\t" << jt->second << "\t" << it->second << endl;
        }
    }
    
    //���ƶȺ�ap���й�
    //int count_ap  = CountCommonAp ( map_q, map_d );
    int count_ap = query_vec.size();
    
    if ( count_ap < 1 ) return 0;
    
    //���ƶȺ�cosֵ�йأ�Ҫ����cos��ǿ���������������
    double cos =  IConsine ( query_vec, data_vec );
    //��������cos
    double sub_cos = SubConsine ( query_vec, data_vec );
    
    if ( cos < sub_cos && sub_cos > 0.9 ) cos = sub_cos;
    
    return cos * count_ap;
    
}

template<typename T>
int KnowledgeSystem::CountCommonAp ( std::map<std::string, T> &map_q, std::map<std::string, T> &map_d )
{
    int count = 0;
    
    for ( typename std::map<std::string, T>::iterator it = map_q.begin(); it != map_q.end(); ++it )
    {
        typename std::map<std::string, T>::iterator jt = map_d.find ( it->first ) ;
        
        if ( jt != map_d.end() )
        {
            count++;
        }
    }
    
    return count;
}

template<typename T>
void KnowledgeSystem::normalize ( std::map<std::string, T> &val )
{
    std::vector<T> vec;
    
    for ( typename std::map<std::string, double>::iterator it = val.begin(); it != val.end(); ++it )
    {
        vec.push_back ( it->second );
    }
    
    //vector����ı�˳��
    normalize ( vec );
    int i = 0;
    
    for ( typename std::map<std::string, T>::iterator it = val.begin(); it != val.end(); ++it )
    {
        it->second = vec[i++];
    }
}

//deprecated
template<typename T>
double KnowledgeSystem::IConsine ( std::map<std::string, T> &map_q, std::map<std::string, T> &map_d )
{
    std::vector<T> query_vec;
    std::vector<T> data_vec;
    
    for ( typename std::map<std::string, T>::iterator it = map_q.begin(); it != map_q.end(); ++it )
    {
        typename std::map<std::string, T>::iterator jt = map_d.find ( it->first ) ;
        
        if ( jt != map_d.end() )
        {
            query_vec.push_back ( it->second );
            data_vec.push_back ( jt->second );
            cout << it->first << "\t" << jt->second << "\t" << it->second << endl;
        }
    }
    
    return IConsine ( query_vec, data_vec );
}

template<typename T>
double KnowledgeSystem::IConsine ( const std::vector<T> &vec_q, const std::vector<T> &vec_d )
{
    if ( vec_q.size() != vec_d.size() ) return 0;
    
    if ( vec_q.size() < 1 ) return 0;
    
    if ( vec_q.size() == 1 ) return 0.2;
    
    double norm_q = Norm2 ( vec_q );
    
    double norm_d = Norm2 ( vec_d );
    return DotProduct ( vec_q, vec_d ) / ( norm_q * norm_d ) * ( min ( norm_q, norm_d ) / max ( norm_q, norm_d ) );
}

//deprecated
template<typename T>
double KnowledgeSystem::Consine ( std::map<std::string, T> &map_q, std::map<std::string, T> &map_d )
{
    std::vector<T> query_vec;
    std::vector<T> data_vec;
    
    for ( typename std::map<std::string, T>::iterator it = map_q.begin(); it != map_q.end(); ++it )
    {
        typename std::map<std::string, T>::iterator jt = map_d.find ( it->first ) ;
        
        if ( jt != map_d.end() )
        {
            query_vec.push_back ( it->second );
            data_vec.push_back ( jt->second );
            cout << it->first << "\t" << jt->second << "\t" << it->second << endl;
        }
    }
    
    return Consine ( query_vec, data_vec );
}



//���Ŀǰȡ������ֵ����������ֵ�򿨶���
template <typename T>
double KnowledgeSystem::IAverage ( const std::vector<T> &vec )
{
    int size = vec.size();
    
    if ( size < 1 ) return 0;
    
    if ( size == 1 ) return vec[0];
    
    T max = vec[0];
    T min = vec[0];
    T sum = vec[0];
    
    for ( int i = 1; i < size; ++i )
    {
        if ( vec[i] > max ) max = vec[i];
        
        if ( vec[i] < min ) min = vec[i];
        
        sum += vec[i];
    }
    
    return ( sum - max - min ) / ( double ) ( size - 2.0 );
}

template <typename T>
void KnowledgeSystem::normalize ( std::vector<T> &vec )
{
    double len = Norm2 ( vec );
    
    for ( int i = 0; i < vec.size(); ++i )
    {
        vec[i] = vec[i] / len;
    }
}

template <typename T>
double KnowledgeSystem::Distance_Euclid ( const std::vector<T> &vec_q, const std::vector<T> &vec_d )
{
    if ( vec_q.size() != vec_d.size() ) return 0;
    
    double ret = 0;
    
    for ( int i = 0; i < vec_d.size(); ++i )
    {
        ret += ( vec_d[i] - vec_q[i] ) * ( vec_d[i] - vec_q[i] );
    }
    
    return ret;
}

template <typename T>
double KnowledgeSystem::Consine ( const std::vector<T> &vec_q, const std::vector<T> &vec_d )
{
    if ( vec_q.size() != vec_d.size() ) return 0;
    
    if ( vec_q.size() < 1 ) return 0;
    
    return DotProduct ( vec_q, vec_d ) / ( Norm2 ( vec_q ) * Norm2 ( vec_d ) );
}

//math.h
template <typename T>
double KnowledgeSystem::Norm2 ( const  std::vector<T> &vec )
{
    double ret = 0;
    
    for ( int i = 0; i < vec.size(); ++i )
    {
        ret += vec[i] * vec[i];
    }
    
    return  sqrt ( ret ) ;
}

template<typename T>
double KnowledgeSystem::DotProduct ( const std::vector<T> &vec_q, const  std::vector<T> &vec_d )
{
    if ( vec_q.size() != vec_d.size() ) return 0;
    
    double ret = 0;
    
    for ( int i = 0; i < vec_d.size(); ++i )
    {
        ret += vec_q[i] * vec_d[i];
    }
    
    return ret;
}
template<typename T>
class comp
{
    public :
        bool operator () ( const std::pair<std::string, T> &a, const std::pair<std::string, T> &b )
        {
            return  a.second < b.second;
        }
};

#endif