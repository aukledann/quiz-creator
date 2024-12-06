// Question.h
// Created by annab on 03.11.2024.

#ifndef QUIZZ_CREATOR_QUESTION_H
#define QUIZZ_CREATOR_QUESTION_H

#include <iostream>
#include <map>
#include <variant>
#include"True_Or_False_Question.h"
#include<vector>
using namespace std;

using Content_type = variant<string, vector<string>>;

class Question {
    int points;

    string question_content;
    string answer;

public:
    Question();
    double ask_points();
    ~Question();


    vector<string> create_wrong_answers(string question_content, Content_type answer);

};

#endif // QUIZZ_CREATOR_QUESTION_H
