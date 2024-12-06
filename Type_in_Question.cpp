//
// Created by annab on 03.11.2024.
//

#include "Type_in_Question.h"


string  Type_in_Question::create_q(){
    cout << "Write the question:";
    string input;
    getline(cin, input);
    return input;
}
string  Type_in_Question::create_a(){
    cout << "Write the answer:";
    string input;
    getline(cin, input);
    return input;
}

string Type_in_Question::answer_q(string question_content, string answer) {
    cout << "Enter the answer: ";
    string ans;
    cin >> ans;
    if((ans == answer) ){
        cout << "Correct!" << endl;//add points here
        return "True";
    }
    else{
        cout << "Incorrect!" << endl;
        return "False";
    }
}


bool Type_in_Question::operator<(const Type_in_Question& other) const{
    return question_content < other.question_content;
}

bool Type_in_Question::operator==(const Type_in_Question& other) const{
    return question_content == other.question_content;
}