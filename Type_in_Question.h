//
// Created by annab on 03.11.2024.
//
#pragma once
#ifndef QUIZZ_CREATOR_TYPE_IN_QUESTION_H
#define QUIZZ_CREATOR_TYPE_IN_QUESTION_H
#include"Question.h";
#include <iostream>
using namespace std;

class Type_in_Question {
    string question_content;
    string answer;

public:
    string answer_q(string question_content, string answer);
    bool operator<(const Type_in_Question& other) const;
    bool operator==(const Type_in_Question& other) const;

    string create_q();
    string create_a();
};


#endif //QUIZZ_CREATOR_TYPE_IN_QUESTION_H
