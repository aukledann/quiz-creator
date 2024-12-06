//
// Created by annab on 03.11.2024.
//

#include "New_Quiz.h"

int New_Quiz::num_questions = 0;
double New_Quiz::points_overall = 0;

New_Quiz::New_Quiz() {}

New_Quiz::New_Quiz(std::string_view name): quiz_name(name) {
}

void New_Quiz::increase_qty() {
    num_questions++;
}
int New_Quiz::get_qty(){
    cout << "Number of questions in a quiz: " << num_questions << endl;
    return  num_questions;
}
void New_Quiz::increase_ov_points(double pts){
    points_overall += pts;
}

void  New_Quiz::append_num_map(int num, Content_type q){
    num_and_question[num] = q;
}

void  New_Quiz::append_question_map(Content_type q, Question_type type_t){
    question_and_type[q] = type_t;
}
void  New_Quiz::append_answer_map(Content_type q, Answer_type type_a){
    question_and_answer[q] = type_a;
}
void New_Quiz::append_points_map(Content_type q,  double pts){
    question_and_points[q] = pts;
}

Answer_type& New_Quiz::operator[](const Content_type& key) {
    return question_and_answer[key];  // Access or insert a value in the map
}


void New_Quiz::delete_record(int index) {
    string to_del;
    vector<string> to_del1;
    auto it = num_and_question.find(index);
    int found = 0;


    if (it != num_and_question.end()) {
        if (holds_alternative<string>(it->second)) {
            to_del = get<string>(it->second);
        } else if (holds_alternative<vector<string>>(it->second)) {
            to_del1 = get<vector<string>>(it->second);
        }
        num_and_question.erase(it);
    }

    for (auto iter = num_and_question.begin(); iter != num_and_question.end();) {
        if (iter->first > index) {
            int new_key = iter->first - 1;
            Content_type value = iter->second;
            num_and_question.erase(iter++);
            num_and_question[new_key] = value;
        } else {
            ++iter;
        }
    }

    for(auto it = question_and_type.begin(); it != question_and_type.end();){
        if (holds_alternative<string>(it->first) && get<string>(it->first) == to_del){
            it = question_and_type.erase(it);  // Erase and move to next element
        }
        else if(holds_alternative<vector<string>>(it->first) && get<vector<string>>(it->first) == to_del1){
            it = question_and_type.erase(it);  // Erase and move to next element
        }
        else {
            ++it;
        }
    }

    for(auto it = question_and_answer.begin(); it != question_and_answer.end();){
        if (holds_alternative<string>(it->second) && get<string>(it->second) == to_del){
            it = question_and_answer.erase(it);  // Erase and move to next element
        }
        else if(holds_alternative<vector<string>>(it->second) && get<vector<string>>(it->second) == to_del1){
            it = question_and_answer.erase(it);  // Erase and move to next element
        }
        else {
            ++it;
        }
    }


}


string New_Quiz::get_correct_sa(int n){
    int i = 0;
    for (const auto& qa : question_and_answer) {
        if (i == n && holds_alternative<vector<string>>(qa.second)) {
            const auto& answers = std::get<std::vector<std::string>>(qa.second);
            for (auto &el: answers) {
                auto found = el.find("wrong_ans_");
                if(found != string::npos){
                    continue;
                }
                else{
                    return el;
                }
            }
        }

        i++;
    }
}


vector<string> New_Quiz::get_all_correct_ma(int n) {
    vector<string> v;
    int i = 0;
    for (const auto& qa : question_and_answer) {
        if (i == n && holds_alternative<vector<string>>(qa.second)) {
            const auto& answers = std::get<std::vector<std::string>>(qa.second);
            for (auto &el: answers) {
                auto found = el.find("wrong_ans_");
                if(found != string::npos){
                    continue;
                }
                else{
                   v.push_back(el);
                }
            }
        }

        i++;
    }
    return v;
}

vector<string> New_Quiz::get_questions(){
    vector<string> v;


    for(auto [qu, ans] : question_and_answer){

        if(holds_alternative<string>(qu)){
            v.push_back(get<string>(qu));
        }
        else if(holds_alternative<vector<string>>(qu)){
            auto vec = get<vector<string>>(qu);
            string first = vec[1] + "... (Match)";
            v.push_back(first);
        }

    }
    return v;
}


vector<string> New_Quiz::get_q_m(int n ) {
    vector<string> v;

    int i = 0;
    for (const auto &qa: question_and_answer) {
        if (i == n && holds_alternative<vector<string>>(qa.first)) {
            v = get<vector<string>>(qa.first);
            return v;
        }
        i++;
    }
}


map<string,string>  New_Quiz::get_all_m(int n){
    map<string,string> mp;
    vector<string> first;
    vector<string> second;

    int i = 0;
    for (const auto &qa: question_and_answer) {
        if (i == n && holds_alternative<vector<string>>(qa.first)) {
            first = get<vector<string>>(qa.first);
            second = get<vector<string>>(qa.second);
            for(int i = 0; i < first.size(); i++){
                mp[first[i]] = second[i];
            }
            return mp;
        }
        i++;
    }
}


string New_Quiz::get_question_text(int n){
    int i = 0;
    for (const auto& qa : question_and_answer) {
        if (i == n && holds_alternative<string>(qa.first)) {
            return get<string>(qa.first);
        }
        i++;
    }
}

vector<string> New_Quiz::get_answers(int n){
    vector<string> v;
    int i = 0;
    for (auto qa : question_and_answer) {
        if (i == n && holds_alternative<vector<string>>(qa.second)) {
           return v = get<vector<string>>(qa.second);
        }
        i++;
    }

    return v;
}

string New_Quiz::get_answer_text(int n){
    int i = 0;
    for (const auto& qa : question_and_answer) {
        if (i == n && holds_alternative<string>(qa.second)) {
            return get<string>(qa.second);
        }
        i++;
    }
}

string New_Quiz::get_type(int n) {
    string str;
    int i = 0;
    for (const auto& qt : question_and_type) {
        if (i == n) {
            return std::visit([](const auto& question) -> string {
                using T = decay_t<decltype(question)>;
                if constexpr (is_same_v<T, True_Or_False_Question>) return "TF";
                else if constexpr (is_same_v<T, Type_in_Question>) return "TP";
                else if constexpr (is_same_v<T, Single_Answer_Question>) return "SA";
                else if constexpr (is_same_v<T, Multiple_Answer_Question>) return "MA";
                else if constexpr (is_same_v<T, Match_Question>) return "M";
                else if constexpr (is_same_v<T, Essay_Question>) return "E";
                else return "Unknown";
            }, qt.second);
        }
        i++;
    }


}

void New_Quiz::Print_all_questions(){
    for (const auto& [key, value] : num_and_question) { // Range-based for loop for clarity
        cout << "Question number " << key << ": ";
        if (holds_alternative<string>(value)) {
            cout << get<string>(value);
            cout << endl;
        } else if (holds_alternative<vector<string>>(value)) {
            // Handle vector<string> case
            for (const auto& q : get<vector<string>>(value)) {
                cout << q << " ";
            }
            cout << endl;
        }
    }


    for(auto [qu, ans] : question_and_answer){


        if(holds_alternative<string>(qu)){
            cout << "Question: " << get<string>(qu) << ", ";
        }
        else if(holds_alternative<vector<string>>(qu)){
            cout << "List of Questions: ";
            for(auto el: get<vector<string>>(qu)){
                cout << el << "  ";
            }
            cout << endl;
        }

        if(holds_alternative<vector<string>>(ans)){
            cout << "List of answers: ";
            for(auto el1: get<vector<string>>(ans)){
                cout << el1 << "  ";
            }
            cout << endl;
        }
        else if(holds_alternative<string>(ans)){
            cout << "Answer: " << get<string>(ans) << endl;
        }
    }

    for(auto [qu, pts] : question_and_points){
        cout << "Points: " << pts <<  endl;//Print question and answer
    }
}

void New_Quiz::Print_ov_points(){
    cout <<"Overall points of this quiz: " << points_overall << endl;
}


New_Quiz::~New_Quiz(){};

