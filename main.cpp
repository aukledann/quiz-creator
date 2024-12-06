#include <iostream>
#include "Question.h"
#include "New_Quiz.h"


#include<string>
#include <SFML/Graphics.hpp>
#include"Button.h"
#include"TextBox.h"
#include <random>
#include <algorithm>
using namespace std;
enum State{CREATE_QUIZ,ENTER_NAME, CREATE_QUESTION,SEE_QUESTIONS, PLAY_QUIZ, CHOOSE_TYPE,SA_FIRST,SA_SEC,MA_FIRST,MA_SEC,TP_FIRST,TP_SEC,TF_FIRST,TF_SEC,M_FIRST,M_SEC, Add_wrong_SA,Add_wrong_MA};
State curr_state = CREATE_QUIZ;


enum Play_states{PLAY_QUIZ1, TP_Play,Correct_TP, Incorrect_TP,Correct_TF,Incorrect_TF,TF_Play, SA_Play, MA_Play, Incorrect_MA,  M_Play, Correct_M, Incorrect_M};
Play_states curr_play_state;
using namespace sf;

sf::Font font;
New_Quiz quiz;
random_device rd;
mt19937 g(rd());
Button create_btn_main(int n){
    return Button( "Q " + std::to_string(n + 1),  sf::Color::Black,50, sf::Color(153,153,255),{1000,50});
}
Button create_btn_delete(int n){
    return Button( "Delete ",  sf::Color::Black,50, sf::Color(153,153,255),{150,50});
}
Button create_btn_edit(int n){
    return Button( "Edit ",  sf::Color::Black,50, sf::Color(153,153,255),{150,50});
}
vector<Button> create_list_edits(int num_quest){
    vector<Button> buttons_edit;
    float exp = 350;
    for(int i = 0; i < num_quest; i++){
        Button new_b = create_btn_edit(i);
        new_b.SetFont(font);
        new_b.setPosition({1250, exp});
        buttons_edit.push_back(new_b);
        exp += 70.0f;
    }
    return buttons_edit;
}

vector<Text> create_list_inccorr_ma(int num_quest){
    vector<string>answers = quiz.get_answers(num_quest);
    vector<string>corr_answers;
    vector<Text> boxes;
    float exp = 550;
    for(int i = 0; i < answers.size(); i++){
        auto found = answers[i].find("wrong_ans_");
        if(found != string::npos){
            continue;
        }
        else{
            corr_answers.push_back(answers[i]);
        }
    }



    for(int i = 0; i < corr_answers.size(); i++){
        Text box;
        box.setFont(font);
        box.setFillColor(sf::Color::Black);
        box.setCharacterSize(100);
        box.setPosition({200, exp});
        box.setString(corr_answers[i]);
        boxes.push_back(box);
        exp += 100.0f;

    }
    return boxes;
}

vector<Text> create_list_inccorr_m(int num_quest) {
    map<string,string> mp = quiz.get_all_m(num_quest);

    vector<string> fir;
    float exp = 550;
    for (const auto &qa: mp) {
        fir.push_back(qa.first + " = " + qa.second);
    }

    vector<Text> boxes;
    for (int i = 0; i < fir.size(); i++) {
        Text box;
        box.setFont(font);
        box.setFillColor(sf::Color::Black);
        box.setCharacterSize(100);
        box.setPosition({200, exp});
        box.setString(fir[i]);
        boxes.push_back(box);
        exp += 100.0f;

    }
    return boxes;
}


vector<Button> create_list_answers(int num_quest){
    vector<string>answers = quiz.get_answers(num_quest);
    vector<Button> buttons;
    float exp = 550;
    for(int i = 0; i < answers.size(); i++){
        string remove_wrong;
        auto found = answers[i].find("wrong_ans_");
        if(found != string::npos){
            remove_wrong = answers[i].substr(10);
        }
        else{
            remove_wrong = answers[i];
        }
        Button new_b (remove_wrong,  sf::Color::Black,70, sf::Color(153,153,255),{800,80});
        new_b.SetFont(font);
        new_b.setPosition({200, exp});
        buttons.push_back(new_b);
        exp += 100.0f;
    }
    return buttons;
}

vector<Button> create_list_m_first(int num_quest){
    vector<string>first = quiz.get_q_m(num_quest);
    shuffle(first.begin(),first.end(),g);
    vector<Button> buttons;
    float exp = 350;
    for(int i = 0; i < first.size(); i++){
        Button new_b (first[i],  sf::Color::Black,70, sf::Color(153,153,255),{650,80});
        new_b.SetFont(font);
        new_b.setPosition({150, exp});
        buttons.push_back(new_b);
        exp += 100.0f;
    }
    shuffle(buttons.begin(),buttons.end(),g);
    return buttons;

}

vector<Button> create_list_m_sec(int num_quest){
    vector<string>answers = quiz.get_answers(num_quest);
    shuffle(answers.begin(),answers.end(),g);
    vector<Button> buttons;
    float exp = 350;
    for(int i = 0; i < answers.size(); i++){
        Button new_b (answers[i],  sf::Color::Black,70, sf::Color(153,153,255),{650,80});
        new_b.SetFont(font);
        new_b.setPosition({1000, exp});
        buttons.push_back(new_b);
        exp += 100.0f;
    }

    shuffle(buttons.begin(),buttons.end(),g);
    return buttons;
}


Play_states get_next_state(int nth){
    string type = quiz.get_type(nth);

    if (type == "TP") {
        curr_play_state = TP_Play;
    } else if (type == "TF") {
        curr_play_state = TF_Play;
    } else if (type == "SA") {
        curr_play_state = SA_Play;
    } else if (type == "MA") {
        curr_play_state = MA_Play;
    } else if (type == "M") {
        curr_play_state = M_Play;
    }

    return curr_play_state;
}


void play_quiz(RenderWindow &window, int num_q) {
    curr_play_state = PLAY_QUIZ1;

    Button btn_ok_play("Ok", sf::Color::Black,80, sf::Color(153,153,255),{300,80});
    btn_ok_play.SetFont(font);
    btn_ok_play.setPosition({1350,1000});

    sf::Text quest_number;
    quest_number.setFont(font);
    quest_number.setCharacterSize(100);
    quest_number.setFillColor(sf::Color::Black);
    quest_number.setPosition({200,100});

    sf::Text text_quest_play;
    text_quest_play.setFont(font);
    text_quest_play.setCharacterSize(100);
    text_quest_play.setFillColor(sf::Color::Black);
    text_quest_play.setPosition({200,250});
    text_quest_play.setStyle(sf::Text::Bold);

    sf::Text text_tp;
    text_tp.setFont(font);
    text_tp.setCharacterSize(100);
    text_tp.setFillColor(sf::Color::Black);
    text_tp.setPosition({200,400});
    text_tp.setString("Type In The Answer: ");

    sf::Text text_m;
    text_m.setFont(font);
    text_m.setCharacterSize(100);
    text_m.setFillColor(sf::Color::Black);
    text_m.setPosition({200,200});
    text_m.setString("Match Questions With Answers");

    sf::Text text_tf;
    text_tf.setFont(font);
    text_tf.setCharacterSize(100);
    text_tf.setFillColor(sf::Color::Black);
    text_tf.setPosition({200,400});
    text_tf.setString("Choose The Answer: ");

    Button btn_True("True", sf::Color::Black,80, sf::Color(153,153,255),{200,80});
    btn_True.SetFont(font);
    btn_True.setPosition({200,560});

    Button btn_False("False", sf::Color::Black,80, sf::Color(153,153,255),{200,80});
    btn_False.SetFont(font);
    btn_False.setPosition({500,560});

    sf::Text text_correct;
    text_correct.setFont(font);
    text_correct.setCharacterSize(100);
    text_correct.setFillColor(sf::Color::Black);
    text_correct.setPosition({200,400});
    text_correct.setString("Correct");

    sf::Text text_incorrect;
    text_incorrect.setFont(font);
    text_incorrect.setCharacterSize(100);
    text_incorrect.setFillColor(sf::Color::Black);
    text_incorrect.setPosition({200,400});
    text_incorrect.setString("Incorrect");

    Button btn_bckgrnd("", sf::Color::Black,80, sf::Color::White,{1200,80});
    btn_bckgrnd.SetFont(font);
    btn_bckgrnd.setPosition({200,530});

    TextBox TP_Play_input(100,sf::Color::Black);
    TP_Play_input.SetFont(font);
    TP_Play_input.SetPosition({200,500});
    TP_Play_input.SetLimit(30);


    int nth = 0;
    int last = 0;
    vector<Button> buttons_f = create_list_m_first(nth);
    vector<Button> buttons_s = create_list_m_sec(nth);
    shuffle ( buttons_s.begin(), buttons_s.end() ,g);
    vector<Button> buttons = create_list_answers(nth);
    vector<Text> boxes = create_list_inccorr_ma(nth);
    vector<Text> boxes_m_fir = create_list_inccorr_m(nth);

    string ans_sa;


    string cor_ans_str;
    sf::Text correct_answer;
    correct_answer.setFont(font);
    correct_answer.setCharacterSize(100);
    correct_answer.setFillColor(sf::Color::Black);
    correct_answer.setPosition({200,500});

    string answ_tf;
    quest_number.setString("Question No: " + to_string(nth));


    vector<string> corrects_ma;
    vector<string>user_ma;
    map<Button, bool> press_depress;
    for(int i = 0; i < buttons.size(); i++) {
        press_depress[buttons[i]] = false;
    }

    map<string, string> user_m;

    map<Button, bool> press_depress_f;
    for(int i = 0; i < buttons_f.size(); i++) {
        press_depress_f[buttons_f[i]] = false;
    }


    map<Button, bool> press_depress_s;
    for(int i = 0; i < buttons_s.size(); i++) {
        press_depress_s[buttons_s[i]] = false;
    }

    string fir = "";
    string sec = "";

    string fir_alr = "";
    string sec_alr = "";



    vector<sf::Color> colors = {Color::Yellow, Color::Magenta, sf::Color(0,255,255), sf::Color(255,128,0),sf::Color(102,255,128),sf::Color(153,51,255)};
    int clr = 0;
    bool first_clicked = false;
    bool second_clicked = false;
    int ind_f = -1;
    int ind_s = -1;

    int alr_inf_f = -1;
    int alr_ind_s = -1;
    map<Button,Button>occup_buttnos_m;
    vector<Button>allowed_f = buttons_f;
    vector<bool> all_f;
    vector<bool> all_s;
    vector<Button>allowed_s;

    int pair_removed  = 0;


    while (nth != num_q && window.isOpen()) {
        sf::Event event_play;

        if(last == 1){
            break;
        }

        if(curr_play_state != Correct_TP && curr_play_state != Incorrect_TP  && curr_play_state != Correct_TF && curr_play_state != Incorrect_TF && curr_play_state != Incorrect_MA && curr_play_state != Incorrect_M) {
            string type = quiz.get_type(nth);

            if (type == "TP") {
                curr_play_state = TP_Play;
                text_quest_play.setString("Question Text: " + quiz.get_question_text(nth));
                quest_number.setString("Question No: " + to_string(nth));
            } else if (type == "TF") {
                curr_play_state = TF_Play;
                text_quest_play.setString("Question Text: " + quiz.get_question_text(nth));
                quest_number.setString("Question No " + to_string(nth));
            } else if (type == "SA") {
                curr_play_state = SA_Play;
                text_quest_play.setString("Question Text: " + quiz.get_question_text(nth));
                quest_number.setString("Question No: " + to_string(nth));
                buttons = create_list_answers(nth);
            } else if (type == "MA") {
                curr_play_state = MA_Play;
                press_depress.clear();
                text_quest_play.setString("Question Text: " + quiz.get_question_text(nth));
                quest_number.setString("Question No: " + to_string(nth));
                buttons = create_list_answers(nth);
                for(int i = 0; i < buttons.size(); i++) {
                    press_depress[buttons[i]] = false;
                }
            } else if (type == "M" &&  curr_play_state != M_Play) {
                curr_play_state = M_Play;
                buttons_f = create_list_m_first(nth);

                buttons_s = create_list_m_sec(nth);
                int size = buttons_f.size();
                all_f.resize(size);
                for(auto el: all_f){
                    el = true;
                }

                int size1 = buttons_s.size();
                all_s.resize(size1);
                for(auto el: all_s){
                    el = true;
                }
            }
        }


        while (window.pollEvent(event_play)) {
            if (event_play.type == Event::Closed) {
                window.close();
            }

           if (event_play.type == sf::Event::MouseMoved) {


                if (btn_ok_play.mouse_over_button(window)) {
                    btn_ok_play.change_btn_col(sf::Color(0, 0, 204));
                }
                else {
                    btn_ok_play.change_btn_col(sf::Color(153, 153, 255));
                }

                if (btn_True.mouse_over_button(window)) {
                    btn_True.change_btn_col(sf::Color(0, 0, 204));
                } else {
                    btn_True.change_btn_col(sf::Color(153, 153, 255));
                }

                if (btn_False.mouse_over_button(window)) {
                    btn_False.change_btn_col(sf::Color(0, 0, 204));
                } else {
                    btn_False.change_btn_col(sf::Color(153, 153, 255));
                }

            }

            if (event_play.type == Event::MouseButtonPressed) {
                if (btn_ok_play.mouse_over_button(window) && curr_play_state == TP_Play) {
                    if(TP_Play_input.get_Text() == quiz.get_answer_text(nth)){
                        TP_Play_input.empty_input();
                        curr_play_state = Correct_TP;
                        cout << "Correct TP" << endl;
                    }
                    else{
                        curr_play_state = Incorrect_TP;
                        TP_Play_input.empty_input();
                        cout << "Incorrect TP" << endl;
                        cor_ans_str = quiz.get_answer_text(nth);
                        correct_answer.setString("Correct Answer: " + cor_ans_str);
                    }
                }

                else  if (btn_True.mouse_over_button(window) && curr_play_state == TF_Play) {
                    answ_tf = "True";
                }
                else  if (btn_False.mouse_over_button(window) && curr_play_state == TF_Play) {
                    answ_tf = "False";
                }
                else  if (btn_ok_play.mouse_over_button(window) && curr_play_state == TF_Play) {
                    if(answ_tf == quiz.get_answer_text(nth) ){
                        curr_play_state = Correct_TF;
                        cout << "Correct TF" << endl;
                    }
                    else{
                        curr_play_state = Incorrect_TF;
                        cout << "Incorrect TF" << endl;
                        cor_ans_str = quiz.get_answer_text(nth);
                        correct_answer.setString("Correct Answer: " + cor_ans_str);
                    }
                }
                else if (btn_ok_play.mouse_over_button(window) && curr_play_state == SA_Play) {
                    if(ans_sa == quiz.get_correct_sa(nth)){
                        curr_play_state = Correct_TP;
                        cout << "Correct SA" << endl;
                    }
                    else{
                        curr_play_state = Incorrect_TP;
                        cout << "Incorrect SA" << endl;
                    }
                }

                else if (btn_ok_play.mouse_over_button(window) && curr_play_state == MA_Play) {
                    corrects_ma = quiz.get_all_correct_ma(nth);
                    sort(corrects_ma.begin(), corrects_ma.end());
                    sort(user_ma.begin(), user_ma.end());


                    cout<< "corects: ";
                    for(auto &el: corrects_ma){
                        if(el == ""){
                            el.erase();
                        }
                        cout << el << endl;
                    }
                    cout << "Size corects: " << corrects_ma.size() << endl;

                    cout<< "user entered: ";
                    for(auto &el: user_ma){
                        cout << el << endl;
                    }
                    cout << "Size users: " << user_ma.size() << endl;
                    if(corrects_ma == user_ma){
                        curr_play_state = Correct_TP;
                        cout << "Correct MA" << endl;
                    }
                    else{
                        curr_play_state = Incorrect_MA;
                        cout << "Incorrect MA" << endl;
                    }
                }

                else if (btn_ok_play.mouse_over_button(window) && curr_play_state == M_Play) {
                    for(auto[key, val]: user_m){
                        cout << key << " , " << val << endl;
                    }


                    if(user_m == quiz.get_all_m(nth)){
                        curr_play_state = Correct_TP;
                        cout << "Correct M" << endl;
                    }
                    else{
                        curr_play_state = Incorrect_M;
                        cout << "Incorrect M" << endl;
                    }
                }

                else if (btn_ok_play.mouse_over_button(window) && curr_play_state == Incorrect_MA) {
                    boxes = create_list_inccorr_ma(nth);
                    cout << "Increase MA" << endl;
                    nth++;
                    if (nth != num_q) {
                        curr_play_state = get_next_state(nth);
                    } else {
                        break;//this was the last question
                    }
                }

                else if (btn_ok_play.mouse_over_button(window) && curr_play_state == Incorrect_M) {
                    boxes_m_fir = create_list_inccorr_m(nth);
                    cout << "Increase M" << endl;
                    nth++;
                    if (nth != num_q) {
                        curr_play_state = get_next_state(nth);
                    } else {
                        break;//this was the last question
                    }
                }

                else if (btn_ok_play.mouse_over_button(window) && (curr_play_state == Correct_TP ||curr_play_state == Incorrect_TP) ) {
                    cout << "Increase TP" << endl;
                    nth++;
                    if (nth != num_q) {
                        curr_play_state = get_next_state(nth);
                    } else {
                        break;//this was the last question
                    }
                }

                else if (btn_ok_play.mouse_over_button(window) && (curr_play_state == Correct_TF ||curr_play_state == Incorrect_TF) ) {
                    cout << "Increase  TF" << endl;
                    nth++;
                    if (nth != num_q) {
                        curr_play_state = get_next_state(nth);
                    } else {
                        break;//this was the last question
                    }
                }
                else{
                    if(curr_play_state == SA_Play){
                        for(int i = 0; i < buttons.size(); i++){
                            if(buttons[i].mouse_over_button(window)) {
                                ans_sa = buttons[i].get_text_on_btn();
                            }
                        }
                    }
                    else if(curr_play_state == MA_Play){

                        for(int i = 0; i < buttons.size(); i++){
                            if(buttons[i].mouse_over_button(window)) {
                                if(press_depress[buttons[i]] == false){
                                    user_ma.push_back(buttons[i].get_text_on_btn());
                                    cout << "User pressed: " << buttons[i].get_text_on_btn() << endl;
                                    buttons[i].change_btn_col(sf::Color(0, 0, 204));
                                }
                                else{
                                    press_depress[buttons[i]] = false;
                                    auto it = std::find(user_ma.begin(), user_ma.end(), buttons[i].get_text_on_btn());
                                    if (it != user_ma.end()) {
                                        user_ma.erase(it); // Remove button from the vector
                                    }
                                    cout << "User depressed: " << buttons[i].get_text_on_btn() << endl;
                                    buttons[i].change_btn_col(sf::Color(153, 153, 255));
                                }
                            }
                        }
                    }
                    else{
                        int flag = 0;
                        int flag1 = 0;

                        for(int i = 0; i < buttons_f.size(); i++){
                            if(buttons_f[i].mouse_over_button(window) && all_f[i] == false) {//part of pair that alr created
                                all_f[i] = true;
                                press_depress_f[buttons_f[i]] = false;
                                alr_inf_f = i;
                                fir_alr = buttons_f[i].get_text_on_btn();
                                sec_alr = user_m[fir_alr];
                                buttons_f[i].change_btn_col(sf::Color(153, 153, 255));
                                user_m.erase(fir_alr);
                                cout << "Depressed part of pair a ";//delete a pair, leave right pressed

                                for(int j = 0; j < buttons_s.size(); j++){
                                    if(buttons_s[j].get_text_on_btn() == sec_alr){
                                        ind_f = -1;
                                        ind_s = j;
                                        second_clicked = true;
                                        first_clicked = false;
                                        clr--;
                                        break;
                                    }
                                }
                                pair_removed = 1;

                                flag = 1;
                            }
                        }

                        if(flag == 1){
                            flag = 0;
                            continue;
                        }




                        for(int i = 0; i < buttons_s.size(); i++){
                            if(buttons_s[i].mouse_over_button(window) && all_s[i] == false && pair_removed == 0) {//part of pair that alr created
                                all_s[i] = true;
                                press_depress_s[buttons_s[i]] = false;
                                alr_ind_s = i;

                                //get string of key, remove from map by it
                                sec_alr = buttons_s[i].get_text_on_btn();

                                for(auto [key,val]: user_m){
                                    if(val == sec_alr){
                                        fir_alr = key;
                                    }
                                }
                                user_m.erase(fir_alr);
                                buttons_s[i].change_btn_col(sf::Color(153, 153, 255));
                                cout << "Depressed part of pair b ";//delete a right, leave left pressed

                                for (int j = 0; j < buttons_f.size(); j++) {
                                    if (buttons_f[j].get_text_on_btn() == fir_alr) {
                                        ind_s = -1;
                                        ind_f = j;
                                        second_clicked = false;
                                        first_clicked = true;
                                        clr--;
                                        break;
                                    }
                                }

                                flag1 = 1;
                            }
                        }
                        if(flag1 == 1){
                            flag1 = 0;
                            continue;
                        }


                        if((second_clicked == false && first_clicked == false) || (second_clicked == true && first_clicked == false)){
                            for(int i = 0; i < buttons_f.size(); i++){
                                if(buttons_f[i].mouse_over_button(window) && all_f[i] == true) {
                                    if (press_depress_f[buttons_f[i]] == false) {
                                        press_depress_f[buttons_f[i]] = true;
                                        fir = buttons_f[i].get_text_on_btn();
                                        cout << "User pressed left : " << buttons_f[i].get_text_on_btn() << endl;
                                        first_clicked = true;
                                        if( second_clicked == false && first_clicked == true) {
                                            ind_f = i;
                                            buttons_f[i].change_btn_col(colors[clr]);
                                        }
                                        else if( second_clicked == true && first_clicked == true) {
                                            //remove from allowed_f i, and from allowed_s ind_s
                                            all_f[i] = false;
                                            all_s[ind_s] = false;
                                            ind_s = -1;
                                            buttons_f[i].change_btn_col(colors[clr++]);
                                            cout << "Pair!" << endl;
                                            user_m[fir] = sec;
                                            fir = "";
                                            sec = "";
                                            first_clicked = false;
                                            second_clicked = false;
                                        }
                                    }
                                    else if(press_depress_f[buttons_f[i]] == true){//kinda useless
                                        press_depress_f[buttons_f[i]] = false;
                                        cout << "User depressed left: " << buttons_f[i].get_text_on_btn() << endl;
                                    }
                                }
                            }
                        }
                        else if(second_clicked == false && first_clicked == true && ind_s == -1){//when we need to pressed button thats not in the pair yet
                            if ((buttons_f[ind_f].mouse_over_button(window) && press_depress_f[buttons_f[ind_f]] == true)) {
                                press_depress_f[buttons_f[ind_f]] = false;
                                cout << "User depressed left gg: " << buttons_f[ind_f].get_text_on_btn() << endl;
                                buttons_f[ind_f].change_btn_col(sf::Color(153, 153, 255));
                                ind_f = -1;
                                first_clicked = false;
                            }
                        }

                        if((second_clicked == false && first_clicked == false) || (second_clicked == false && first_clicked == true)) {
                            for (int i = 0; i < buttons_s.size(); i++) {
                                if (buttons_s[i].mouse_over_button(window) && all_s[i] == true) {
                                    if (press_depress_s[buttons_s[i]] == false) {
                                        press_depress_s[buttons_s[i]] = true;
                                        sec = buttons_s[i].get_text_on_btn();
                                        cout << "User pressed right: " << buttons_s[i].get_text_on_btn() << endl;
                                        second_clicked = true;

                                        if( second_clicked == true && first_clicked == false){
                                            if (buttons_s[i].mouse_over_button(window)) {
                                                ind_s = i;
                                                buttons_s[i].change_btn_col(colors[clr]);
                                            }
                                        }
                                        else if(second_clicked == true && first_clicked == true){
                                            if(buttons_s[i].mouse_over_button(window)) {
                                                buttons_s[i].change_btn_col(colors[clr++]);
                                                cout << "Pair!" << endl;
                                                all_f[ind_f] = false;
                                                all_s[i] = false;
                                                ind_f = -1;
                                            }
                                        }

                                        if (fir != "") {

                                            user_m[fir] = sec;
                                            fir = "";
                                            sec = "";
                                            first_clicked = false;
                                            second_clicked = false;
                                        }
                                    } else {
                                        press_depress_s[buttons_s[i]] = false;
                                        cout << "User depressed right: " << buttons_s[i].get_text_on_btn() << endl;
                                    }
                                }
                            }
                        }
                        else if(second_clicked == true && first_clicked == false && ind_f == -1){//when we need to pressed button thats not in the pair yet
                            if (press_depress_s[buttons_s[ind_s]] == true) {
                                all_s[ind_s] = true;
                                press_depress_s[buttons_s[ind_s]] = false;
                                cout << "User depressed right gg: " << buttons_s[ind_s].get_text_on_btn() << endl;
                                buttons_s[ind_s].change_btn_col(sf::Color(153, 153, 255));
                                ind_s = -1;
                                second_clicked = false;
                            }
                        }
                    }

                }
            }

            if (event_play.type == Event::TextEntered) {
                TP_Play_input.Type_in(event_play);
            }
        }

        window.clear(Color(230, 204, 255));
        if (curr_play_state == TP_Play) {
            btn_bckgrnd.draw_to_window(window);
            window.draw(quest_number);
            window.draw(text_quest_play);
            window.draw(text_tp);
            TP_Play_input.draw_to_window(window);
            btn_ok_play.draw_to_window(window);
        }
        else if(curr_play_state == TF_Play){
            window.draw(quest_number);
            window.draw(text_quest_play);
            window.draw(text_tf);
            btn_True.draw_to_window(window);
            btn_False.draw_to_window(window);
            btn_ok_play.draw_to_window(window);
        }

        else if(curr_play_state == SA_Play){
            window.draw(quest_number);


            window.draw(text_quest_play);
            window.draw(text_tf);
            btn_ok_play.draw_to_window(window);
            if (event_play.type == sf::Event::MouseMoved) {
                for (auto &el: buttons) {
                    if (el.mouse_over_button(window)) {

                        el.change_btn_col(sf::Color(0,0,204));
                    } else {
                        el.change_btn_col(sf::Color(153,153,255));
                    }
                }


            }
            for (auto& button : buttons) {
                button.draw_to_window(window);
            }


        }

        else if(curr_play_state == MA_Play){
            window.draw(quest_number);
            window.draw(text_quest_play);
            window.draw(text_tf);

            btn_ok_play.draw_to_window(window);
            if (event_play.type == sf::Event::MouseMoved) {
                for (auto &el: buttons) {
                    if (el.mouse_over_button(window)) {

                        el.change_btn_col(sf::Color(0,0,204));
                    } else {
                        el.change_btn_col(sf::Color(153,153,255));
                    }
                }

            }

            for (auto& button : buttons) {
                button.draw_to_window(window);
            }


        }
        else if(curr_play_state == M_Play){
            window.draw(text_m);
            btn_ok_play.draw_to_window(window);

            if (event_play.type == sf::Event::MouseMoved) {
                for (auto &el: buttons_f) {
                    if (el.mouse_over_button(window) && el.get_color() != sf::Color::Yellow) {
                        //el.change_btn_col(sf::Color(0, 0, 204));
                    }
                    else {
                        //el.change_btn_col(sf::Color(153, 153, 255));
                    }

                }
            }


            if (event_play.type == sf::Event::MouseButtonPressed) {
                for(int i = 0; i < buttons_f.size(); i++){
                    if (buttons_f[i].mouse_over_button(window)) {
                        //buttons_f[i].change_btn_col(colors[clr]);
                    }
                }


                for(int i = 0; i < buttons_s.size(); i++){
                    if (buttons_s[i].mouse_over_button(window) && buttons_f[i].get_color() == colors[clr]) {
                        //buttons_s[i].change_btn_col(colors[clr++]);
                    }
                }
            }


            for (auto& button : buttons_f) {
                button.draw_to_window(window);
            }
            for (auto& button : buttons_s) {
                button.draw_to_window(window);
            }
        }

        else if(curr_play_state == Correct_TP){
            btn_ok_play.draw_to_window(window);
            window.draw(text_correct);
        }
        else if(curr_play_state == Incorrect_TP){
            window.draw(correct_answer);
            btn_ok_play.draw_to_window(window);
            window.draw(text_incorrect);
        }
        else if(curr_play_state == Correct_TF){
            btn_ok_play.draw_to_window(window);
            window.draw(text_correct);
        }
        else if(curr_play_state == Incorrect_TF){
            window.draw(correct_answer);
            btn_ok_play.draw_to_window(window);
            window.draw(text_incorrect);
        }
        else if(curr_play_state == Incorrect_MA){
            btn_ok_play.draw_to_window(window);
            window.draw(text_incorrect);
            for (auto& box : boxes) {
                window.draw(box);
            }
        }

        else if(curr_play_state == Incorrect_M){
            btn_ok_play.draw_to_window(window);
            window.draw(text_incorrect);

            for (auto& box : boxes_m_fir) {
                window.draw(box);
            }
        }
        window.display();
    }
}




vector<Button> create_list_deletes(int num_quest){
    vector<Button> buttons_del;
    float exp = 350;
    for(int i = 0; i < num_quest; i++){
        Button new_b = create_btn_delete(i);
        new_b.SetFont(font);
        new_b.setPosition({1450, exp});
        buttons_del.push_back(new_b);
        exp += 70.0f;
    }
    return buttons_del;
}
vector<Button> create_list_questions(int num_quest){
    vector<string>questions = quiz.get_questions();
    vector<Button> buttons;
    float exp = 350;
    for(int i = 0; i < num_quest; i++){
        Button new_b (to_string(i + 1) + ") " + questions[i],  sf::Color::Black,50, sf::Color(153,153,255),{1000,50});
        new_b.SetFont(font);
        new_b.setPosition({200, exp});
        buttons.push_back(new_b);
        exp += 70.0f;
    }
    return buttons;
}


int main() {

    RenderWindow window(sf::VideoMode(1800, 1200), "Quiz Creator");

    sf::CircleShape shape;
    sf::Text txt;
    font.loadFromFile("C:/Users/annab/Projects/test_Window/Cake Christmas.ttf");
    txt.setString("Welcome To Quiz Creator!");
    txt.setFont(font);
    txt.setCharacterSize(100);
    txt.setFillColor(sf::Color::Black);
    txt.setStyle(sf::Text::Bold);
    window.draw(txt);
    txt.setPosition(500.f, 400.f);


    sf::Text wrong1;
    wrong1.setString("option1");
    wrong1.setFont(font);
    wrong1.setCharacterSize(100);
    wrong1.setFillColor(sf::Color::Black);
    wrong1.setPosition(200, 400);

    sf::Text wrong2;
    wrong2.setString("option2");
    wrong2.setFont(font);
    wrong2.setCharacterSize(100);
    wrong2.setFillColor(sf::Color::Black);
    wrong2.setPosition(200, 500);

    sf::Text wrong3;
    wrong3.setString("option3");
    wrong3.setFont(font);
    wrong3.setCharacterSize(100);
    wrong3.setFillColor(sf::Color::Black);
    wrong3.setPosition(200, 600);


    sf::Text chose_q;
    chose_q.setString("Choose The Type Of Question");
    chose_q.setFont(font);
    chose_q.setCharacterSize(100);
    chose_q.setFillColor(sf::Color::Black);
    chose_q.setPosition(200, 300);


    sf::Text enter_ans;
    enter_ans.setString("Enter The Answer");
    enter_ans.setFont(font);
    enter_ans.setCharacterSize(100);
    enter_ans.setFillColor(sf::Color::Black);
    enter_ans.setPosition(200, 300);

    sf::Text enter_que;
    enter_que.setString("Enter The Question");
    enter_que.setFont(font);
    enter_que.setCharacterSize(100);
    enter_que.setFillColor(sf::Color::Black);
    enter_que.setPosition(200, 300);

    sf::Text choose_ans;
    choose_ans.setString("Choose The Correct Answer");
    choose_ans.setFont(font);
    choose_ans.setCharacterSize(100);
    choose_ans.setFillColor(sf::Color::Black);
    choose_ans.setPosition(200, 300);


    sf::Text add_wron_opts;
    add_wron_opts.setString("Add Wrong Options(Up To 3)");
    add_wron_opts.setFont(font);
    add_wron_opts.setCharacterSize(100);
    add_wron_opts.setFillColor(sf::Color::Black);
    add_wron_opts.setPosition(200, 300);


    sf::Font font1;
    Button btn_first("Create New Quiz", sf::Color::Black,80, sf::Color(153,153,255),{500,100});
    btn_first.SetFont(font);
    btn_first.setPosition({650,600});


    Button btn_sec("", sf::Color::White,0, sf::Color::White,{850,80});
    btn_sec.SetFont(font);
    btn_sec.setPosition({500,600});

    TextBox input(100,sf::Color::Black);
    input.SetFont(font);
    input.SetPosition({500,565});
    input.SetLimit(30);


    Button btn_MA("Multiple Answers", sf::Color::Black,80, sf::Color(153,153,255),{430,80});
    btn_MA.SetFont(font);
    btn_MA.setPosition({200,500});

    Button btn_SA("Single Answer", sf::Color::Black,80, sf::Color(153,153,255),{430,80});
    btn_SA.SetFont(font);
    btn_SA.setPosition({700,500});

    Button btn_TP("Type In", sf::Color::Black,80, sf::Color(153,153,255),{430,80});
    btn_TP.SetFont(font);
    btn_TP.setPosition({1200,500});

    Button btn_TF("True/False", sf::Color::Black,80, sf::Color(153,153,255),{430,80});
    btn_TF.SetFont(font);
    btn_TF.setPosition({200,700});

    Button btn_M("Match", sf::Color::Black,80, sf::Color(153,153,255),{430,80});
    btn_M.SetFont(font);
    btn_M.setPosition({700,700});

    sf::Text txt2;
    sf::Text type_q;
    type_q.setFont(font);
    type_q.setCharacterSize(100);
    type_q.setFillColor(sf::Color::Black);


    Button btn_True("True", sf::Color::Black,80, sf::Color(153,153,255),{200,80});
    btn_True.SetFont(font);
    btn_True.setPosition({200,560});

    Button btn_False("False", sf::Color::Black,80, sf::Color(153,153,255),{200,80});
    btn_False.SetFont(font);
    btn_False.setPosition({500,560});

    Button btn_create_question("Create New Question", sf::Color::Black,80, sf::Color(153,153,255),{700,100});
    btn_create_question.SetFont(font);
    btn_create_question.setPosition({550,400});

    Button btn_see_question("See Existing Questions", sf::Color::Black,80, sf::Color(153,153,255),{700,100});
    btn_see_question.SetFont(font);
    btn_see_question.setPosition({550,530});

    Button btn_play_quiz("Play The Quiz", sf::Color::Black,80, sf::Color(153,153,255),{700,100});
    btn_play_quiz.SetFont(font);
    btn_play_quiz.setPosition({550,660});

    Button btn_add_sa("Add", sf::Color::Black,80, sf::Color(153,153,255),{300,100});
    btn_add_sa.SetFont(font);
    btn_add_sa.setPosition({200,550});

    Button btn_add_ma("Add", sf::Color::Black,80, sf::Color(153,153,255),{300,100});
    btn_add_ma.SetFont(font);
    btn_add_ma.setPosition({200,550});

    Button btn_add_ma_wr("Add", sf::Color::Black,80, sf::Color(153,153,255),{300,100});
    btn_add_ma_wr.SetFont(font);
    btn_add_ma_wr.setPosition({200,550});

    Button btn_done("Done", sf::Color::Black,80, sf::Color(153,153,255),{300,80});
    btn_done.SetFont(font);
    btn_done.setPosition({1400,1000});
    btn_done.setPosition({1400,1000});

    sf::Text enter_que_and_answ;
    enter_que_and_answ.setString("Enter The Question and Corresponding Answer(Up To 4)");
    enter_que_and_answ.setFont(font);
    enter_que_and_answ.setCharacterSize(80);
    enter_que_and_answ.setFillColor(sf::Color::Black);
    enter_que_and_answ.setPosition(200, 300);

    Button btn_add_pair("Add Pair", sf::Color::Black,80, sf::Color(153,153,255),{300,80});
    btn_add_pair.SetFont(font);
    btn_add_pair.setPosition({200,550});


    TextBox first_pair(80,sf::Color::Black);
    first_pair.SetFont(font);
    first_pair.SetPosition({200,430});
    first_pair.SetLimit(60);


    Button btn_bck1("", sf::Color::Black, 0, sf::Color::White,{1400,80});
    btn_bck1.SetFont(font);
    btn_bck1.setPosition({200,450});

    Button btn_back("Back", sf::Color::Black,80, sf::Color(153,153,255),{300,80});
    btn_back.SetFont(font);
    btn_back.setPosition({200,1000});


    int count_wrongs = 0;
    int count_multiples = 0;
    int count_wrong_multiples = 0;
    int count_pairs = 0;

    string qstn;
    string answ;


    Type_in_Question type_tp;
    True_Or_False_Question type_tf;
    Single_Answer_Question type_sa;
    vector<string> all_answers_sa(6);
    int in1 = 0;
    Multiple_Answer_Question type_ma;
    vector<string> all_answers_ma(6);
    int in = 0;

    Match_Question type_m;
    vector<string> first_m_part(6);
    vector<string> sec_m_part(6);
    int in2 = 0;
    string str;


    int num_q = 0;
    sf::Text see_num_q;
    see_num_q.setFont(font);
    see_num_q.setCharacterSize(100);
    see_num_q.setFillColor(sf::Color::Black);
    see_num_q.setPosition({200,200});
    see_num_q.setString("Number Of Questions:" + to_string(num_q));
    //vector<Button> buttons = create_list_questions(num_q);
    vector<Button> buttons;
    vector<Button> buttons_to_del = create_list_deletes(num_q);
    vector<Button> buttons_to_edit = create_list_edits(num_q);

    int ind_to_del = 0;

    auto seed = unsigned ( std::time(0) );


    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseMoved) {
                if (btn_first.mouse_over_button(window)) {
                    btn_first.change_btn_col(sf::Color(0, 0, 204));
                } else {
                    btn_first.change_btn_col(sf::Color(153, 153, 255));
                }

                if(btn_create_question.mouse_over_button(window)){
                    btn_create_question.change_btn_col(sf::Color(0,0,204));
                }
                else{
                    btn_create_question.change_btn_col(sf::Color(153,153,255));
                }
                if(btn_see_question.mouse_over_button(window)){
                    btn_see_question.change_btn_col(sf::Color(0,0,204));
                }
                else{
                    btn_see_question.change_btn_col(sf::Color(153,153,255));
                }

                if(btn_back.mouse_over_button(window)){
                    btn_back.change_btn_col(sf::Color(0,0,204));
                }
                else{
                    btn_back.change_btn_col(sf::Color(153,153,255));
                }

                if(btn_play_quiz.mouse_over_button(window)){
                    btn_play_quiz.change_btn_col(sf::Color(0,0,204));
                }
                else{
                    btn_play_quiz.change_btn_col(sf::Color(153,153,255));
                }

                if(btn_MA.mouse_over_button(window)){
                    btn_MA.change_btn_col(sf::Color(0,0,204));
                }
                else{
                    btn_MA.change_btn_col(sf::Color(153,153,255));
                }

                if(btn_SA.mouse_over_button(window)){
                    btn_SA.change_btn_col(sf::Color(0,0,204));
                }
                else{
                    btn_SA.change_btn_col(sf::Color(153,153,255));
                }

                if(btn_TP.mouse_over_button(window)){
                    btn_TP.change_btn_col(sf::Color(0,0,204));
                }
                else{
                    btn_TP.change_btn_col(sf::Color(153,153,255));
                }

                if(btn_TF.mouse_over_button(window)){
                    btn_TF.change_btn_col(sf::Color(0,0,204));
                }
                else{
                    btn_TF.change_btn_col(sf::Color(153,153,255));
                }

                if(btn_M.mouse_over_button(window)){
                    btn_M.change_btn_col(sf::Color(0,0,204));
                }
                else{
                    btn_M.change_btn_col(sf::Color(153,153,255));
                }

                if(btn_True.mouse_over_button(window)){
                    btn_True.change_btn_col(sf::Color(0,0,204));
                }
                else{
                    btn_True.change_btn_col(sf::Color(153,153,255));
                }

                if(btn_False.mouse_over_button(window)){
                    btn_False.change_btn_col(sf::Color(0,0,204));
                }
                else{
                    btn_False.change_btn_col(sf::Color(153,153,255));
                }
                if(btn_add_sa.mouse_over_button(window)){
                    btn_add_sa.change_btn_col(sf::Color(0,0,204));
                }
                else{
                    btn_add_sa.change_btn_col(sf::Color(153,153,255));
                }

                if(btn_add_ma.mouse_over_button(window)){
                    btn_add_ma.change_btn_col(sf::Color(0,0,204));
                }
                else{
                    btn_add_ma.change_btn_col(sf::Color(153,153,255));
                }

                if(btn_add_ma_wr.mouse_over_button(window)){
                    btn_add_ma_wr.change_btn_col(sf::Color(0,0,204));
                }
                else{
                    btn_add_ma_wr.change_btn_col(sf::Color(153,153,255));
                }

                if(btn_done.mouse_over_button(window)){
                    btn_done.change_btn_col(sf::Color(0,0,204));
                }
                else{
                    btn_done.change_btn_col(sf::Color(153,153,255));
                }

                if(btn_add_pair.mouse_over_button(window)){
                    btn_add_pair.change_btn_col(sf::Color(0,0,204));
                }
                else{
                    btn_add_pair.change_btn_col(sf::Color(153,153,255));
                }


                for(auto &el: buttons_to_del){
                    if(el.mouse_over_button(window)){
                        el.change_btn_col(sf::Color(0,0,204));
                    }
                    else{
                        el.change_btn_col(sf::Color(153,153,255));
                    }
                }

                for(auto &el: buttons_to_edit){
                    if(el.mouse_over_button(window)){
                        std::cout << "Mouse Over Button: "<< std::endl;
                        el.change_btn_col(sf::Color(0,0,204));
                    }
                    else{
                        el.change_btn_col(sf::Color(153,153,255));
                    }
                }

            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (btn_first.mouse_over_button(window)) {
                    std::cout << "button pressed" << std::endl;

                    if (curr_state == CREATE_QUIZ) {
                        curr_state = ENTER_NAME;
                        txt.setString("Enter The Name Of Your Quiz");
                        btn_first.reuse_btn("Ok!", sf::Color::Black, 80, sf::Color(153, 153, 255), {100, 80});
                        btn_first.SetFont(font);
                        btn_first.setPosition({1400, 600});
                    } else if (curr_state == ENTER_NAME) {
                        curr_state = CREATE_QUESTION;
                        string name_quiz = input.get_Text();
                        New_Quiz quiz(name_quiz);//create a quiz
                        txt.setString("Quiz Name: " + name_quiz);
                        txt.setPosition(200.f, 100.f);
                    }
                    else if (curr_state == TF_FIRST) {
                        qstn = input.get_Text();
                        cout << "Question_TF: " << qstn << endl;
                        quiz.append_question_map(qstn,type_tf);
                        quiz.append_num_map(num_q,qstn);

                        curr_state = TF_SEC;
                        btn_first.setPosition({200, 700});
                    }
                    else if (btn_first.mouse_over_button(window) && curr_state == TF_SEC) {
                        cout << "Answer_TF: " << answ << endl;
                        quiz.append_answer_map(qstn, answ);
                        num_q++;
                        curr_state = CREATE_QUESTION;
                    }

                    else if (btn_first.mouse_over_button(window) && curr_state == TP_SEC) {
                         answ =  input.get_Text();
                         cout << "Answer_TP: " << answ << endl;
                         quiz.append_answer_map(qstn,answ);
                         num_q++;
                         curr_state = CREATE_QUESTION;
                    }

                    else if (curr_state == TP_FIRST) {
                        qstn =  input.get_Text();
                        cout << "Question_TP: " << qstn << endl;
                        quiz.append_question_map(qstn,type_tp);
                        quiz.append_num_map(num_q,qstn);

                        curr_state = TP_SEC;
                        input.empty_input();
                        input.SetPosition({200, 420});
                        input.SetLimit(50);
                        btn_sec.reuse_btn("", sf::Color::Black, 0, sf::Color::White, {1300, 80});
                        btn_sec.setPosition({200, 450});
                        btn_sec.SetFont(font);
                        btn_first.setPosition({200, 550});
                    }
                    else if (curr_state == SA_FIRST) {
                        qstn = input.get_Text();
                        cout << "Question_SA: " << qstn << endl;
                        quiz.append_question_map(qstn,type_sa);
                        quiz.append_num_map(num_q,qstn);


                        curr_state = SA_SEC;
                        input.empty_input();
                        input.SetPosition({200, 420});
                        input.SetLimit(50);
                        btn_sec.reuse_btn("", sf::Color::Black, 0, sf::Color::White, {1300, 80});
                        btn_sec.setPosition({200, 450});
                        btn_sec.SetFont(font);
                        btn_first.setPosition({200, 550});
                    }
                    else if (curr_state == MA_FIRST) {
                        qstn = input.get_Text();
                        cout << "Question_MA: " << qstn << endl;
                        quiz.append_question_map(qstn,type_ma);
                        quiz.append_num_map(num_q,qstn);

                        curr_state = MA_SEC;
                        input.empty_input();
                        input.Type_in(event);
                        input.SetPosition({200, 420});
                        input.SetLimit(50);
                        btn_sec.reuse_btn("", sf::Color::Black, 0, sf::Color::White, {1300, 80});
                        btn_sec.setPosition({200, 450});
                        btn_sec.SetFont(font);
                    }
                    else if (curr_state == SA_SEC) {
                        answ = input.get_Text();
                       // all_answers_sa.insert(all_answers_sa.begin(),answ);
                       all_answers_sa[in1++] = answ;
                        cout << "Answer_SA: " << all_answers_sa[0] << endl;
                        //quiz.append_answer_map(qstn, answ);

                        curr_state = Add_wrong_SA;
                        btn_sec.reuse_btn("", sf::Color::White, 0, sf::Color::White, {1300, 80});
                        input.empty_input();
                        input.SetPosition({200, 420});
                        input.SetLimit(50);
                        num_q++;
                    }
                }

                else if (btn_play_quiz.mouse_over_button(window) && curr_state == CREATE_QUESTION) {
                    curr_state = PLAY_QUIZ;
                    play_quiz(window, num_q);
                    curr_state = CREATE_QUESTION;
                }
                else if (btn_create_question.mouse_over_button(window) && curr_state == CREATE_QUESTION) {
                    curr_state = CHOOSE_TYPE;
                }
                else if (btn_back.mouse_over_button(window) && curr_state == CHOOSE_TYPE) {
                    curr_state = CREATE_QUESTION;
                }
                else if (btn_back.mouse_over_button(window) && curr_state == TP_FIRST) {
                    curr_state = CHOOSE_TYPE;
                }
                else if (btn_back.mouse_over_button(window) && curr_state == TF_FIRST) {
                    curr_state = CHOOSE_TYPE;
                }
                else if (btn_back.mouse_over_button(window) && curr_state == SA_FIRST) {
                    curr_state = CHOOSE_TYPE;
                }
                else if (btn_back.mouse_over_button(window) && curr_state == MA_FIRST) {
                    curr_state = CHOOSE_TYPE;
                }

                else if (btn_see_question.mouse_over_button(window) && curr_state == CREATE_QUESTION) {
                    curr_state = SEE_QUESTIONS;
                    buttons = create_list_questions(num_q);
                    buttons_to_del = create_list_deletes(num_q);
                    buttons_to_edit = create_list_edits(num_q);
                    quiz.Print_all_questions();
                }
                else if (btn_MA.mouse_over_button(window) && curr_state == CHOOSE_TYPE) {
                    std::cout << "button MA pressed" << std::endl;
                    curr_state = MA_FIRST;
                    btn_first.reuse_btn("Ok!", sf::Color::Black, 80, sf::Color(153, 153, 255), {100, 80});
                    btn_first.setPosition({200, 550});
                    txt.setPosition({200, 100});

                    btn_sec.reuse_btn("", sf::Color::White, 0, sf::Color::White, {1300, 80});
                    btn_sec.SetFont(font);
                    btn_sec.setPosition({200, 450});
                    input.empty_input();
                    input.SetPosition({200, 420});
                    input.SetLimit(50);
                    type_q.setString("Question Type: Multiple Answers");
                    type_q.setPosition({200, 200});
                }
                else if (btn_SA.mouse_over_button(window) && curr_state == CHOOSE_TYPE) {
                    std::cout << "button SA pressed" << std::endl;
                    curr_state = SA_FIRST;
                    btn_first.reuse_btn("Ok!", sf::Color::Black, 80, sf::Color(153, 153, 255), {100, 80});
                    btn_first.setPosition({200, 550});
                    txt.setPosition({200, 100});

                    btn_sec.reuse_btn("", sf::Color::White, 0, sf::Color::White, {1300, 80});
                    btn_sec.SetFont(font);
                    btn_sec.setPosition({200, 450});
                    input.empty_input();
                    input.SetPosition({200, 420});
                    input.SetLimit(50);
                    type_q.setString("Question Type: Single Answer");
                    type_q.setPosition({200, 200});
                }
                else if (btn_TP.mouse_over_button(window) && curr_state == CHOOSE_TYPE) {
                    std::cout << "button TP pressed" << std::endl;
                    curr_state = TP_FIRST;
                    btn_first.reuse_btn("Ok!", sf::Color::Black, 80, sf::Color(153, 153, 255), {100, 80});
                    btn_first.setPosition({200, 550});
                    txt.setPosition({200, 100});

                    btn_sec.reuse_btn("", sf::Color::White, 0, sf::Color::White, {1300, 80});
                    btn_sec.SetFont(font);
                    input.empty_input();
                    btn_sec.setPosition({200, 450});
                    input.SetPosition({200, 420});
                    input.SetLimit(50);
                    type_q.setString("Question Type: Type In");
                    type_q.setPosition({200, 200});
                }
                else if (btn_TF.mouse_over_button(window) && curr_state == CHOOSE_TYPE) {
                    std::cout << "button TF pressed" << std::endl;
                    curr_state = TF_FIRST;
                    btn_first.reuse_btn("Ok!", sf::Color::Black, 80, sf::Color(153, 153, 255), {100, 80});
                    btn_first.setPosition({200, 550});
                    txt.setPosition({200, 100});

                    btn_sec.reuse_btn("", sf::Color::White, 0, sf::Color::White, {1300, 80});
                    btn_sec.SetFont(font);
                    btn_sec.setPosition({200, 450});
                    input.empty_input();
                    input.SetPosition({200, 420});
                    input.SetLimit(50);
                    type_q.setString("Question Type: True/False");
                    type_q.setPosition({200, 200});
                }
                else if (btn_M.mouse_over_button(window) && curr_state == CHOOSE_TYPE) {
                    curr_state = M_FIRST;
                    txt.setPosition({200, 100});
                    type_q.setString("Question Type: Match");
                    type_q.setPosition({200, 200});

                }

                else if (btn_add_pair.mouse_over_button(window) && curr_state == M_FIRST) {
                    str = first_pair.get_Text();
                    quiz.append_num_map(num_q,str);
                    quiz.append_question_map(str,type_m);
                    auto found = str.find_first_of('=');//before = goes to first, after to sec

                    if(found != string::npos){
                        string fp = str.substr(0,found);
                        //first_m_part.push_back( fp);
                        first_m_part[in2] = fp;
                        string sp = str.substr(found+2);
                        //sec_m_part.push_back(sp);
                        sec_m_part[in2++] = sp;
                    }


                    first_pair.empty_input();
                    if (count_pairs == 0) {
                        count_pairs++;
                        btn_bck1.setPosition({200, 535});
                        first_pair.SetPosition({200, 512});
                        btn_add_pair.setPosition({200, 640});
                    }
                    else if (count_pairs == 1) {
                        count_pairs++;
                        btn_bck1.setPosition({200, 640});
                        first_pair.SetPosition({200, 615});
                        btn_add_pair.setPosition({200, 740});
                    }
                    else if (count_pairs == 2) {
                        count_pairs++;
                    }

                }

                else if (btn_add_pair.mouse_over_button(window) && curr_state == M_SEC) {

                    str = first_pair.get_Text();
                    auto found = str.find_first_of('=');//before = goes to first, after to sec

                    first_m_part.push_back( str.substr(0,found));
                    sec_m_part.push_back(str.substr(found+2));

                    first_pair.empty_input();
                    if (count_pairs == 0) {
                        count_pairs++;
                        btn_bck1.setPosition({200, 535});
                        first_pair.SetPosition({200, 512});
                        btn_add_pair.setPosition({200, 640});
                    }
                    else if (count_pairs == 1) {
                        count_pairs++;
                        btn_bck1.setPosition({200, 640});
                        first_pair.SetPosition({200, 615});
                        btn_add_pair.setPosition({200, 740});
                    }
                    else if (count_pairs == 2) {
                        count_pairs++;
                    }

                }
                else if (btn_add_sa.mouse_over_button(window) && curr_state == Add_wrong_SA) {
                    answ = input.get_Text();
                    answ = "wrong_ans_" + answ;
                    int pos = count_wrongs+1;
                    //all_answers_sa.insert(all_answers_sa.begin() + pos,answ);
                    all_answers_sa[in1++] = answ;

                    input.empty_input();
                    input.SetLimit(50);
                    if (count_wrongs == 0) {
                        count_wrongs++;
                        btn_sec.setPosition({200, 535});
                        input.SetPosition({200, 500});
                        btn_add_sa.setPosition({200, 640});
                    }
                    else if (count_wrongs == 1) {
                        count_wrongs++;
                        btn_sec.setPosition({200, 640});
                        input.SetPosition({200, 610});
                        btn_add_sa.setPosition({200, 740});
                    }
                    else if (count_wrongs == 2) {
                        count_wrongs++;
                    }

                }
                else if (btn_add_ma.mouse_over_button(window) && curr_state == MA_SEC) {
                    answ = input.get_Text();
                     all_answers_ma[in++] = answ;


                    input.empty_input();
                    input.SetLimit(50);

                    if (count_multiples == 0) {
                        count_multiples++;
                        btn_sec.setPosition({200, 535});
                        input.SetPosition({200, 500});
                        btn_add_ma.setPosition({200, 640});
                    }
                    else if (count_multiples == 1) {
                        count_multiples++;
                        btn_sec.setPosition({200, 640});
                        input.SetPosition({200, 610});
                        btn_add_ma.setPosition({200, 740});
                    }
                    else if (count_multiples == 2) {
                        count_multiples++;
                    }

                }
                else if (btn_add_ma_wr.mouse_over_button(window) && curr_state == Add_wrong_MA) {
                    answ = input.get_Text();
                    answ = "wrong_ans_" + answ;
                    all_answers_ma[in++] = answ;

                    input.empty_input();
                    input.Type_in(event);
                    input.SetLimit(50);

                    if(count_wrong_multiples == 0){//first add click: wrong 1, move down input, btn_sec, btn_add
                        count_wrong_multiples++;
                        btn_sec.setPosition({200, 535});
                        input.SetPosition({200, 500});
                        btn_add_ma_wr.setPosition({200, 640});
                        wrong1.setPosition({200,400});
                    }

                    else if(count_wrong_multiples == 1){//first add click: wrong 1, move down input, btn_sec, btn_add
                        count_wrong_multiples++;
                        btn_sec.setPosition({200, 630});
                        input.SetPosition({200, 600});
                        btn_add_ma_wr.setPosition({200, 730});
                        wrong2.setPosition({200,500});
                    }
                    else if(count_wrong_multiples == 2){//first add click: wrong 1, move down input, btn_sec, btn_add
                        count_wrong_multiples++;
                        wrong3.setPosition({200,600});
                    }


                }
                else if (btn_done.mouse_over_button(window) && curr_state == Add_wrong_SA) {
                    cout << "All wrongs_sa: ";
                    for(const auto &el: all_answers_sa){
                        cout << el << ", ";
                    }
                    cout << endl;
                    all_answers_sa.erase(
                            std::remove_if(all_answers_sa.begin(), all_answers_sa.end(),
                                           [](const std::string &el) { return el.empty(); }),
                            all_answers_sa.end());

                    shuffle(all_answers_sa.begin(), all_answers_sa.end(),g);
                    quiz.append_answer_map(qstn, all_answers_sa);
                    all_answers_sa.erase(all_answers_sa.begin(),all_answers_sa.end());
                    in1 = 0;

                    curr_state = CREATE_QUESTION;
                    btn_add_sa.setPosition({200, 550});
                    count_wrongs = 0;
                }
                else if (btn_done.mouse_over_button(window) && curr_state == MA_SEC) {
                    curr_state = Add_wrong_MA;
                    btn_add_ma.setPosition({200, 550});
                    input.SetPosition({200, 420});
                    btn_sec.setPosition({200, 450});
                    count_multiples = 0;


                    num_q++;
                }
                else if (btn_done.mouse_over_button(window) && curr_state == Add_wrong_MA) {
                    cout << "All wrongs_ma: ";
                    all_answers_ma.erase(
                            std::remove_if(all_answers_ma.begin(), all_answers_ma.end(),
                                           [](const std::string &el) { return el.empty(); }),
                            all_answers_ma.end());
                    cout << endl;
                    shuffle(all_answers_ma.begin(),all_answers_ma.end(),g);
                    quiz.append_answer_map(qstn, all_answers_ma);
                    all_answers_ma.erase(all_answers_ma.begin(),all_answers_ma.end());
                    in = 0;

                    curr_state = CREATE_QUESTION;
                    btn_add_ma_wr.setPosition({200, 550});
                    count_wrong_multiples = 0;
                }

                else if (btn_done.mouse_over_button(window) && curr_state == M_FIRST) {

                    cout << "Firsts: ";
                    for(auto el:first_m_part){
                        cout << el << ", ";
                    }
                    cout << endl;

                    cout << "Secs: ";
                    for(auto el:sec_m_part){
                        cout << el << ", ";
                    }
                    cout << endl;

                    curr_state = M_SEC;
                    btn_add_pair.setPosition({200,550});
                    count_pairs = 0;
                    btn_bck1.setPosition({200,450});
                    first_pair.empty_input();
                    first_pair.SetPosition({200,430});


                    num_q++;

                }
                else if (btn_done.mouse_over_button(window) && curr_state == M_SEC) {

                    cout << "All Firsts: ";
                    for(auto el:first_m_part){
                        cout << el << ", ";
                    }
                    cout << endl;

                    cout << "All Secs: ";
                    for(auto el:sec_m_part){
                        cout << el << ", ";
                    }
                    cout << endl;

                    first_m_part.erase(
                            std::remove_if(first_m_part.begin(), first_m_part.end(),
                                           [](const std::string &el) { return el.empty(); }),
                            first_m_part.end());
                    cout << endl;

                    sec_m_part.erase(
                            std::remove_if(sec_m_part.begin(), sec_m_part.end(),
                                           [](const std::string &el) { return el.empty(); }),
                            sec_m_part.end());
                    cout << endl;


                    //std::srand ( seed );
                   // std::random_shuffle ( first_m_part.begin(), first_m_part.end() );

                   // std::srand ( seed );
                    //std::random_shuffle ( sec_m_part.begin(), sec_m_part.end() );


                    quiz.append_answer_map(first_m_part, sec_m_part);
                    first_m_part.erase(first_m_part.begin(),first_m_part.end());
                    sec_m_part.erase(sec_m_part.begin(),sec_m_part.end());
                    in2 = 0;




                    curr_state = CREATE_QUESTION;
                    btn_add_pair.setPosition({200,550});
                    btn_bck1.setPosition({200,450});
                    first_pair.SetPosition({200,430});
                    count_pairs = 0;
                }
                else if (btn_M.mouse_over_button(window) && curr_state == CHOOSE_TYPE) {
                    std::cout << "button M pressed" << std::endl;
                }
                else if (btn_True.mouse_over_button(window) && curr_state == TF_SEC) {
                    btn_True.change_btn_col(sf::Color(0, 0, 204));
                    answ = "True";
                }
                else if (btn_False.mouse_over_button(window) && curr_state == TF_SEC) {
                    btn_False.change_btn_col(sf::Color(0, 0, 204));
                    answ = "False";
                }
                else if (btn_done.mouse_over_button(window) && curr_state == SEE_QUESTIONS) {
                    curr_state = CREATE_QUESTION;
                }


                for(int i = 0; i < buttons_to_del.size(); i++){
                    if(buttons_to_del[i].mouse_over_button(window)){
                        cout << "Deleted index: " << i << endl;
                        num_q--;
                        buttons = create_list_questions(num_q);
                        buttons_to_del = create_list_deletes(num_q);
                        buttons_to_edit = create_list_edits(num_q);
                        ind_to_del = i;
                        quiz.delete_record(ind_to_del);
                        quiz.Print_all_questions();
                    }
                }
            }

            if (event.type == sf::Event::TextEntered){
                input.Type_in(event);

                if(curr_state == M_FIRST || curr_state == M_SEC){
                    first_pair.Type_in(event);
                }


            }
        }

        window.clear( Color(230,204,255));
        window.draw(txt);

        if(curr_state == CREATE_QUIZ){
            btn_first.draw_to_window(window);
        }
        else if(curr_state == ENTER_NAME){
            btn_first.draw_to_window(window);
            btn_sec.draw_to_window(window);
            input.draw_to_window(window);
        }
        else if(curr_state == CREATE_QUESTION){
            btn_create_question.draw_to_window(window);
            btn_see_question.draw_to_window(window);
            btn_play_quiz.draw_to_window(window);
        }
        else if(curr_state == SEE_QUESTIONS){
            btn_done.draw_to_window(window);
            see_num_q.setString("Number Of Questions:" + to_string(num_q));

            for (auto& button : buttons) {
                button.draw_to_window(window);
            }

            for (auto& button : buttons_to_del) {
                button.draw_to_window(window);
            }

            for (auto& button : buttons_to_edit) {
                button.draw_to_window(window);
            }

            window.draw(see_num_q);
        }
        else if(curr_state == CHOOSE_TYPE){
            btn_back.draw_to_window(window);
            btn_MA.draw_to_window(window);
            btn_SA.draw_to_window(window);
            btn_TP.draw_to_window(window);
            btn_TF.draw_to_window(window);
            btn_M.draw_to_window(window);
            window.draw(chose_q);
        }
        else if(curr_state == TF_FIRST){
            btn_back.draw_to_window(window);
            btn_first.draw_to_window(window);
            window.draw(enter_que);
            window.draw(type_q);
            btn_sec.draw_to_window(window);
            input.draw_to_window(window);
        }

        else if(curr_state == TF_SEC){
            btn_first.draw_to_window(window);
            btn_True.draw_to_window(window);
            btn_False.draw_to_window(window);
            window.draw(choose_ans);
            window.draw(type_q);
        }
        else if(curr_state == TP_FIRST){
            btn_back.draw_to_window(window);
            btn_first.draw_to_window(window);
            window.draw(enter_que);
            window.draw(type_q);
            btn_sec.draw_to_window(window);
            input.draw_to_window(window);
        }

        else if(curr_state == TP_SEC){
            btn_first.draw_to_window(window);
            window.draw(enter_ans);
            window.draw(type_q);
            btn_sec.draw_to_window(window);
            input.draw_to_window(window);
        }
        else if(curr_state == SA_FIRST){
            btn_back.draw_to_window(window);
            btn_first.draw_to_window(window);
            window.draw(enter_que);
            window.draw(type_q);
            btn_sec.draw_to_window(window);
            input.draw_to_window(window);
        }

        else if(curr_state == SA_SEC){
            btn_first.draw_to_window(window);
            btn_sec.draw_to_window(window);
            input.draw_to_window(window);
            window.draw(enter_ans);
            window.draw(type_q);
        }

        else if(curr_state == MA_FIRST){
            btn_back.draw_to_window(window);
            btn_first.draw_to_window(window);
            window.draw(enter_que);
            window.draw(type_q);
            btn_sec.draw_to_window(window);
            input.draw_to_window(window);
        }
        else if(curr_state == M_FIRST){

            if(count_pairs == 0){//just opened it
                btn_bck1.draw_to_window(window);
                first_pair.draw_to_window(window);
                btn_add_pair.draw_to_window(window);
            }
            else if(count_pairs == 1){//show wrong 1, moved down input, add, btn_sec
                wrong1.setString(str);
                window.draw(wrong1);
                btn_bck1.draw_to_window(window);
                first_pair.draw_to_window(window);
                btn_add_pair.draw_to_window(window);
            }
            else if(count_pairs == 2){
                window.draw(wrong1);
                wrong2.setString(str);
                window.draw(wrong2);
                btn_bck1.draw_to_window(window);
                first_pair.draw_to_window(window);
                btn_add_pair.draw_to_window(window);
            }
            else if(count_pairs == 3){
                window.draw(wrong1);
                window.draw(wrong2);
                wrong3.setString(str);
                window.draw(wrong3);
            }
            window.draw(enter_que_and_answ);
            window.draw(type_q);
            btn_done.draw_to_window(window);
        }


        else if(curr_state == M_SEC){

            if(count_pairs == 0){//just opened it
                btn_bck1.draw_to_window(window);
                first_pair.draw_to_window(window);
                btn_add_pair.draw_to_window(window);
            }
            else if(count_pairs == 1){//show wrong 1, moved down input, add, btn_sec
                wrong1.setString(str);
                window.draw(wrong1);
                btn_bck1.draw_to_window(window);
                first_pair.draw_to_window(window);
                btn_add_pair.draw_to_window(window);
            }
            else if(count_pairs == 2){
                window.draw(wrong1);
                wrong2.setString(str);
                window.draw(wrong2);
                btn_bck1.draw_to_window(window);
                first_pair.draw_to_window(window);
                btn_add_pair.draw_to_window(window);
            }
            else if(count_pairs == 3){
                window.draw(wrong1);
                window.draw(wrong2);
                wrong3.setString(str);
                window.draw(wrong3);
            }

            window.draw(add_wron_opts);
            window.draw(type_q);
            btn_done.draw_to_window(window);
        }



        else if(curr_state == MA_SEC){
            if(count_multiples >= 2){
                wrong2.setString(all_answers_ma[1]);
                window.draw(wrong2);
            }
            if(count_multiples == 3){
                wrong3.setString(all_answers_ma[2]);
                window.draw(wrong3);
            }
            wrong1.setString(all_answers_ma[0]);
            window.draw(wrong1);
            if(count_multiples != 3){
                btn_add_ma.draw_to_window(window);
                btn_sec.draw_to_window(window);
                input.draw_to_window(window);
            }
            btn_done.draw_to_window(window);
            window.draw(enter_ans);
            window.draw(type_q);
        }

        else if(curr_state == Add_wrong_SA){
            if(count_wrongs >= 2){
                wrong2.setString(all_answers_sa[2]);
                window.draw(wrong2);
            }
            if(count_wrongs == 3){
                wrong3.setString(all_answers_sa[3]);
                window.draw(wrong3);
            }
            wrong1.setString(all_answers_sa[1]);
            window.draw(wrong1);
            if(count_wrongs != 3){
                btn_add_sa.draw_to_window(window);
                btn_sec.draw_to_window(window);
                input.draw_to_window(window);
            }
            btn_done.draw_to_window(window);
            window.draw(add_wron_opts);
            window.draw(type_q);

        }

        else if(curr_state == Add_wrong_MA){

            if(count_wrong_multiples == 0){//just opened it
                btn_sec.draw_to_window(window);
                input.draw_to_window(window);
                btn_add_ma_wr.draw_to_window(window);
            }
            else if(count_wrong_multiples == 1){//show wrong 1, moved down input, add, btn_sec
                wrong1.setString(answ);
                window.draw(wrong1);
                btn_sec.draw_to_window(window);
                input.draw_to_window(window);
                btn_add_ma_wr.draw_to_window(window);
            }
            else if(count_wrong_multiples == 2){//show wrong 1, moved down input, add, btn_sec
                window.draw(wrong1);
                wrong2.setString(answ);
                window.draw(wrong2);
                btn_sec.draw_to_window(window);
                input.draw_to_window(window);
                btn_add_ma_wr.draw_to_window(window);
            }
            else if(count_wrong_multiples == 3){//show wrong 1, moved down input, add, btn_sec
                window.draw(wrong1);
                window.draw(wrong2);
                wrong3.setString(answ);
                window.draw(wrong3);
            }

            btn_done.draw_to_window(window);
            window.draw(add_wron_opts);
            window.draw(type_q);

        }



        window.display();
    }

    return 0;
}



// In SeeQuestions: edit logic

//finish logic of M_Play(cancel pairs is broken)
//remove m_sec, add in M_first up to 5 options


//finish second TF: make true/false buttons dark until ok pressed, same for SA_Play, MA_PLAY
//if user clicks play when there are 0 questions: print "0 questions"

//back button for TP_SEC, TF_SEC, MA_SEC, SA_SEC must show the input of prev page
//Make Enter button work for input


//add points for questions
//Set time limit for answers

//wrong input check. Dont allow done until question entered, answer are added



