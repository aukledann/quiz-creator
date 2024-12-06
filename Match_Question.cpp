//
// Created by annab on 08.11.2024.
//

#include "Match_Question.h"


vector<vector<string>> Match_Question::create_match() {

    vector<vector<string>> v(2);
    cout << "How many correct firsts and seconds will you have?";
    int num_first = 0;
    cin >> num_first;
    cin.ignore();

    v[0].resize(num_first);
    v[1].resize(num_first);



    cout << "Enter first values and their corresponding second values: ";
    for(int i = 0; i < num_first; i++){
        string fir, sec;
        getline(cin, fir,'=');
        cin.clear();
        cin.ignore();
        getline(cin >> ws, sec);
        fir_sec[fir] = sec;
        v[0][i] = fir;
        v[1][i] = sec;
    }


    for(auto[f,s]:fir_sec){
        first.push_back(f);
        second.push_back(s);
    }

    cout << "Would you like to add wrong options? [Y/N] ";
    string input;
    getline(cin, input);
    if(input == "Y"){
        vector<vector<string>> v_with_opt = create_wrong_opts(v);
        return v_with_opt;
    }
    else{
        return v;
    }



}

vector<vector<string>> Match_Question::create_wrong_opts( vector<vector<string>> v){
    int input;
    cout << "How many first wrong u want?: ";
    cin >> input;
    cin.ignore();

    string opt;
    for(int i = 0; i < input; i++){
        cout << "Enter wrong options: ";
        getline(cin, opt);
        opt = "wrong__" + opt;
        fir_sec.insert( make_pair(opt,""));
        first.push_back(opt);
        v[0].push_back(opt);
    }

    cout << "How many second wrong u want?: ";
    cin >> input;
    cin.ignore();

    for(int i = 0; i < input; i++){
        cout << "Enter wrong options: ";
        getline(cin, opt);
        opt = "wrong__" + opt;
        fir_sec.insert( make_pair("",opt));
        second.push_back(opt);
        v[1].push_back(opt);
    }
    return v;
}

bool Match_Question::operator<(const Match_Question& other) const{
    return question_content < other.question_content;
}


bool Match_Question::operator==(const Match_Question& other) const{
    return question_content == other.question_content;
}