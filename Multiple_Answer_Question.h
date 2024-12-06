//
// Created by annab on 08.11.2024.
//
#pragma once
#ifndef QUIZZ_CREATOR_MULTIPLE_ANSWER_QUESTION_H
#define QUIZZ_CREATOR_MULTIPLE_ANSWER_QUESTION_H
#include <iostream>
#include<vector>

using namespace std;

class Multiple_Answer_Question {
    vector<string> wrong_options;
    string question_content;
    vector<string> answers;
public:
    string create_q();
    vector<string> create_a();
    vector<string>  create_wrong_opts(vector<string> answers);
    string answer_q(string question_content, vector<string> answer);
    bool operator<(const Multiple_Answer_Question& other) const;
    bool operator==(const Multiple_Answer_Question& other) const;
};


#endif //QUIZZ_CREATOR_MULTIPLE_ANSWER_QUESTION_H
