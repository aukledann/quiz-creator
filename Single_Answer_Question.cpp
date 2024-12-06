//
// Created by annab on 07.11.2024.
//

#include "Single_Answer_Question.h"

string Single_Answer_Question:: create_q(){
    string q;
    cout << "Enter the question:";
    getline(cin, q);
    return q;
}

vector<string> Single_Answer_Question:: create_a(){
    string q;
    cout << "Enter the answer:";
    getline(cin, q);

    cout<< "Do you Want to add wrong options? [Y/N]";
    string wrong;
    getline(cin, wrong);
    if(wrong != "Y"){
        vector<string> v1(1);
        v1.insert(v1.begin(),q);
        return v1;
    }
    else{
        vector<string> vect =  create_wrong_opts(q);
        return vect;
    }


}

vector<string> Single_Answer_Question::create_wrong_opts( string answer) {
    cout << "How many wrong options would you like to add?";
    int num_wrong_options;
    cin >> num_wrong_options;
    cin.ignore();


    int ov_sum = num_wrong_options + 1;
    vector<string> all_opts(ov_sum);
    all_opts.insert(all_opts.begin(),answer);

    cout << "Add wrong options: ";
    for(int i = 1; i < ov_sum; i++){
        string opt;
        getline(cin, opt);
        opt = "wrong_opt" + opt;
        all_opts[i] = opt;
    }

    return all_opts;

}

string Single_Answer_Question::answer_q(string question_content, string answer){

    wrong_options.push_back(answer);//MAKE it random ans not back!

    cout << "Choose an option from 1 to " << wrong_options.size();
    int num = 0;
    int right_num = 0;
    for(auto el: wrong_options){
        cout << num << el;
        if(el == answer){
            right_num = num;
        }
        num++;
    }

    string user_ans;
    getline(cin, user_ans);
    if(user_ans == to_string(right_num)){
        cout << "Correct!" << endl;//add points here
        return "True";
    }
    else{
        cout << "Incorrect!" << endl;
        return "False";
    }


}


bool Single_Answer_Question::operator<(const Single_Answer_Question& other) const{
    return question_content < other.question_content;
}


bool Single_Answer_Question::operator==(const Single_Answer_Question& other) const{
    return question_content == other.question_content;
}