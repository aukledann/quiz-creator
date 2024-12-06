//
// Created by annab on 07.11.2024.
//
#pragma once
#ifndef QUIZZ_CREATOR_SINGLE_ANSWER_QUESTION_H
#define QUIZZ_CREATOR_SINGLE_ANSWER_QUESTION_H
#include <iostream>
#include<vector>
using namespace std;

class Single_Answer_Question {
    vector<string> wrong_options;
    string question_content;
    string answer;
public:

        string create_q();
        vector<string> create_a();
        vector<string> create_wrong_opts( string answer);
        string answer_q(string question_content, string answer);
        bool operator<(const Single_Answer_Question& other) const;
        bool operator==(const Single_Answer_Question& other) const;

};


#endif //QUIZZ_CREATOR_SINGLE_ANSWER_QUESTION_H
