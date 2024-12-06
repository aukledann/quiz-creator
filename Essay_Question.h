//
// Created by annab on 09.11.2024.
//

#ifndef QUIZZ_CREATOR_ESSAY_QUESTION_H
#define QUIZZ_CREATOR_ESSAY_QUESTION_H
using namespace std;
#include<iostream>
#include<vector>
#include<map>

class Essay_Question {

    string topic;
    string text;
public:
    bool operator<(const Essay_Question& other) const;
    bool operator==(const Essay_Question& other) const;

    string create();
};


#endif //QUIZZ_CREATOR_ESSAY_QUESTION_H
