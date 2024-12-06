//
// Created by annab on 03.11.2024.
//

#include "True_Or_False_Question.h"
#include <iostream>
#include <string>
using namespace std;

string  True_Or_False_Question::create_q(){
    cout << "Write the question:";
    string input;
    getline(cin, input);
    return input;
}
string  True_Or_False_Question::create_a(){
    cout << "Write the answer:";
    string input;
    getline(cin, input);
    return input;
}

string True_Or_False_Question::answer_q(string question_content, string answer) {
    cout << "Press T for true or F for False:";
    string ans;
    cin >> ans;
    if((ans == "T" && answer == "True") || (ans == "F" && answer == "False")){
        cout << "Correct!" << endl;//add points here
        return "True";
    }
    else{
        cout << "Incorrect!" << endl;
        return "False";
    }
}


bool True_Or_False_Question::operator<(const True_Or_False_Question& other) const{
    return question_content < other.question_content;
}


bool True_Or_False_Question::operator==(const True_Or_False_Question& other) const{
    return question_content == other.question_content;
}