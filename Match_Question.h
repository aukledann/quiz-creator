//
// Created by annab on 08.11.2024.
//

#ifndef QUIZZ_CREATOR_MATCH_QUESTION_H
#define QUIZZ_CREATOR_MATCH_QUESTION_H
using namespace std;
#include<iostream>
#include<vector>
#include<map>

class Match_Question {
    vector<string>first;
    vector<string>second;
    map<string,string>fir_sec;
    string question_content;

public:
    vector<vector<string>> create_match();
    vector<vector<string>> create_wrong_opts(vector<vector<string>> v);
    bool operator<(const Match_Question& other) const;
    bool operator==(const Match_Question& other) const;

};


#endif //QUIZZ_CREATOR_MATCH_QUESTION_H
