//
// Created by annab on 03.11.2024.
//
#pragma once
#ifndef QUIZZ_CREATOR_TRUE_OR_FALSE_QUESTION_H
#define QUIZZ_CREATOR_TRUE_OR_FALSE_QUESTION_H
#include <iostream>

using namespace std;

class True_Or_False_Question {
    string question_content;
    string answer;
public:
    string answer_q(string question_content, string answer);
    bool operator<(const True_Or_False_Question& other) const;
    bool operator==(const True_Or_False_Question& other) const;



    string create_q();
    string create_a();
};


#endif //QUIZZ_CREATOR_TRUE_OR_FALSE_QUESTION_H
