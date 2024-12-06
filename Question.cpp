// Question.cpp
// Created by annab on 03.11.2024.

#include "Question.h"
#include <iostream>
using namespace std;

Question::Question(){}// Constructor definition

Question::~Question(){}

double Question::ask_points() {
    cout << "Enter points for the question: ";
    double pts;
    cin >> pts;
    cin.ignore();
    return pts;
}


vector<string> Question::create_wrong_answers(string question_content, Content_type answer){
    cout << "How many wrong options would you like to add?";
    int num_wrong_options;
    cin >> num_wrong_options;
    cin.ignore();

    vector<string> wrong_options(num_wrong_options);

    cout << "Add wrong options: ";
    for(int i = 0; i < num_wrong_options; i++){
        string opt;
        getline(cin >> ws, opt);
        wrong_options[i] = opt;
    }
    cout << "Wrong options entered:" << endl;
    for (int i = 0; i < wrong_options.size(); i++) {
        wrong_options[i] = "wrong_option__" + wrong_options[i];
        cout << wrong_options[i] << endl;
    }

    return wrong_options;

}