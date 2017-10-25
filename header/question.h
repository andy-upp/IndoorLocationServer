/********************************************************************
	Author:		Wang Yu
	Created:	2013/07/10
	Revised:	2013/07/29   15:33
	File Base:	question

	Purpose:	�����ʾ�����������õ�����Ŀ��question
            ��ʾ�û��ύ�Ĵ𰸻��׼��QuestionAns��
*********************************************************************/
#ifndef EVAL_QUESTION_H_
#define EVAL_QUESTION_H_

#include "stdafx.h"



struct QuestionAns
{
    std::string person_id;
    std::string ques_id;
    std::vector<int> ans;
    boost::posix_time::ptime submission_time;
};

// ��Ŀ���Ϳ���Ϊ��ѡ��Ҳ����Ϊ��ѡ����Ŀѡ����������
// ���������ʱload
// Note: ÿһ����Ŀ�������Լ�ѡ�����ݼ������������ܶ���600��
class question
{
    public:
        typedef std::vector<question> QuestionVec;
        typedef std::map<std::string, question> QuestionMap;
        typedef std::map<std::string, question*> QuestionPtrMap;
        question();
        question ( const question& ques );
        question ( const std::string& id,
                   const std::string& stem,
                   const std::vector<std::string>& options,
                   const std::vector<int>& answers,
                   const std::vector<std::string>& img_names,
                   const double& full_score,
                   const boost::posix_time::ptime& entry_time );

        inline void set_qid ( const std::string& id )
        {
            qid_ = id;
        }
        inline const std::string& qid() const
        {
            return qid_;
        }

        void set_stem ( const std::string& stem );
        const std::string& stem() const;

        void set_options ( const std::vector<std::string>& options );
        const std::vector<std::string>& options() const;

        void set_answers ( const std::vector<int>& answers );
        const std::vector<int>& answers() const;

        void set_img_names ( const std::vector<std::string>& img_names );
        const std::vector<std::string>& img_names() const;

        void set_full_score ( const double full_score );
        const double full_score() const;

        void set_category ( const std::string& categoty );
        const std::string& category() const;

        void set_role ( const std::string& role );
        const std::string& role() const;

        void set_difficulty ( const std::string& difficulty );
        const std::string& difficulty() const;

        void set_entry_time ( const boost::posix_time::ptime& entry_time ); // unimplemented
        void set_entry_time ( const time_t& entry_time );
        const boost::posix_time::ptime& entry_time() const;

        /*   template <typename Archive>
        void serialize ( Archive& ar, const unsigned int version )
        {
        ar & qid_;
        ar & stem_;
        ar & category_;
        ar & role_;
        ar & difficulty_;
        ar & options_;
        ar & answers_;
        ar & img_names_;
        ar & full_score_;
        }*/

    private:
        std::string qid_;
        std::string stem_;//��Ŀ����
        std::string category_;
        std::string role_;
        std::string difficulty_;
        std::vector<std::string> options_;//ѡ��
        std::vector<int> answers_;
        std::vector<std::string> img_names_;//�����·��
        double full_score_;
        boost::posix_time::ptime entry_time_;
        /*

          boost::shared_ptr<eval_manager> ele_mgr_;
          std::string question_cut_id_;*/
};
#endif