//
// Created by annab on 09.11.2024.
//

#include "Essay_Question.h"


string  Essay_Question::create(){
    cout << "Write the topic of the essay: ";
    string input;
    getline(cin, input);
    return input;
}



bool Essay_Question::operator<(const Essay_Question& other) const{
    return topic < other.topic;
}


bool Essay_Question::operator==(const Essay_Question& other) const{
    return topic == other.topic;
}