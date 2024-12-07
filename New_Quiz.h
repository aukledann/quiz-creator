//
// Created by annab on 03.11.2024.
//
#pragma once
#ifndef QUIZZ_CREATOR_NEW_QUIZ_H
#define QUIZZ_CREATOR_NEW_QUIZ_H

#include <string>
#include<vector>
#include"Question.h"
#include"True_Or_False_Question.h"
#include"Type_in_Question.h"
#include"Single_Answer_Question.h"
#include"Multiple_Answer_Question.h"
#include"Match_Question.h"
#include"Essay_Question.h"

using namespace std;
using Question_type = variant<True_Or_False_Question, Type_in_Question,Single_Answer_Question, Multiple_Answer_Question,Match_Question,Essay_Question>;
using Content_type = variant<string, vector<string>>;
using Answer_type = variant<string, vector<string>>;



class New_Quiz {

string quiz_name;
static int num_questions;
static double points_overall;
map<int , Content_type> num_and_question;
map< Content_type, Question_type>question_and_type;
map<Content_type , Answer_type> question_and_answer;
map<Content_type, double> question_and_points;
public:


    New_Quiz();
    New_Quiz(std::string_view name);//constructor
    ~New_Quiz();//destructor

    void increase_qty();
    int get_qty();
    void increase_ov_points(double pts);


    void append_num_map(int num, Content_type q);
    void append_question_map(Content_type q,Question_type type_t);
    void append_answer_map(Content_type q, Answer_type type_a);
    void append_points_map(Content_type q,  double pts);
    void del_by_key(int nth);


    void Print_all_questions();
    void Print_ov_points();

    vector<string>get_questions();


    void delete_record(int index);
    Answer_type& operator[](const Content_type& key);

    string get_type(int n);
    string get_question_text(int n);
    vector<string> get_answers(int n);
    string get_answer_text(int n);

    string get_correct_sa(int n );
    vector<string> get_all_correct_ma(int n );
    vector<string> get_q_m(int n );
    map<string,string>  get_all_m(int n );


};



#endif //QUIZZ_CREATOR_NEW_QUIZ_H
