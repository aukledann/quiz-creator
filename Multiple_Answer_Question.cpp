//
// Created by annab on 08.11.2024.
//

#include "Multiple_Answer_Question.h"

string Multiple_Answer_Question:: create_q(){
    string q;
    cout << "Enter the question:";
    getline(cin, q);
    return q;
}


vector<string> Multiple_Answer_Question::create_a(){


    cout << "How many correct answers will this question have? ";
    int num_ans = 0;
    cin >> num_ans;
    cin.ignore();
    vector<string>vector_ans(num_ans);


    cout <<  "Enter the answers";
    string input;
    for(int i = 0; i < num_ans; i++){
        getline(cin, input);
        vector_ans.push_back(input);
    }

    string wrong;
    cout<< "Do you Want to add wrong options? [Y/N]";
    getline(cin, wrong);
    if(wrong != "Y"){
        return vector_ans;
    }
    else{
       vector<string> vect =  create_wrong_opts(vector_ans);
       return vect;
    }


    //return vector_ans;
}

vector<string>  Multiple_Answer_Question::create_wrong_opts(vector<string> answers){


    cout << "How many wrong options would you like to add?";
    int num_wrong_options;
    cin >> num_wrong_options;
    cin.ignore();

    int size_ans = answers.size();
    int ov_size = num_wrong_options+ size_ans;
    vector<string> all_options(ov_size);
    for(int i = 0 ; i < size_ans; i++){
        all_options[i] = answers[i];
    }

    cout << "Add wrong options: ";
    for(int i = size_ans; i < ov_size; i++){
        string opt;
        getline(cin, opt);
        opt = "wrong_opt" + opt;
        all_options[i] = opt;
    }

    return all_options;
}

bool Multiple_Answer_Question::operator<(const Multiple_Answer_Question& other) const{
    return question_content < other.question_content;
}


bool Multiple_Answer_Question::operator==(const Multiple_Answer_Question& other) const{
    return question_content == other.question_content;
}