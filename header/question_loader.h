/********************************************************************
	Author:		Wang Yu
	Created:	2013/07/10
	Revised:	2013/08/09   15:40
	File Base:	datafile_util

	Purpose:	��Ŀ�����ࡣ
            �ṩ�����ļ��Ķ�ȡ���޸ġ����棬���ṩ�����ӿڿ��Ի�ȡ��Ŀ���ݡ�
*********************************************************************/
#ifndef LOAD_DATA_QUESTION_LOADER_H_
#define LOAD_DATA_QUESTION_LOADER_H_

#include "question.h"

struct tm;
class TiXmlElement;

// Possible usage:
// QuestionLoader instance("myfile");
// instance.Load(questions, question_map);
class QuestionLoader
{
    public:
        QuestionLoader() {}
        QuestionLoader ( const std::string& file_name );
        QuestionLoader ( const char* file_name );
        ~QuestionLoader() {}

        inline const std::string& file_name() const
        {
            return file_name_;
        }
        inline void set_file_name ( const std::string& path )
        {
            file_name_ = path;
        }

        // ��ȡ�ļ������е���Ŀ�������questions��question_map��
        // question_map������ĿidΪkey������map����
        // ������Ŀ������
        int Load ( question::QuestionVec* question_list,
                   question::QuestionPtrMap* question_ptr_map );

        int Load ( question::QuestionPtrMap* question_ptr_map );

        question* CreateQuestionPtr ( TiXmlElement* ques_element );
        const question& CreateQuestion ( TiXmlElement* ques_element );

    private:
        // ���ļ����ַ�����ʽ������ת��Ϊtime_t
        time_t ParseTimeT ( const char* time_in_string );
        // ͨ����Ŀ��Ԫ�ؽڵ������ѡ��ʹ�
        void ParseOptionsAndAnswers ( const TiXmlElement& ques_element, //��Ŀ��Ԫ�ؽڵ�
                                      std::vector<std::string>* options,
                                      std::vector<int>* answers );
        // ����ʾȫ��ͼƬ���Ƶ�һ�����ַ����ָ��������ɶ������
        void ParseImageNames ( const char* images, std::vector<std::string>* img_names );
        char* UTF8ToGBK ( const char* in );

        std::string file_name_;
};


class TextFileUtil
{
    public:
        bool parseFile ( std::string file, std::vector<std::string> &segs );
        static void split ( const std::string str, std::vector<std::string> &vec, char token );
};

#endif