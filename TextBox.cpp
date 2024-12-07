//
// Created by annab on 12.11.2024.
//

#include "TextBox.h"


TextBox::TextBox(int size, sf::Color color){
    text.setCharacterSize(size);
    text.setFillColor(color);
}
void TextBox::SetLimit(int lim){
    limit = lim;
}

void TextBox::SetText(string str){
    text.setString(str);
}

void TextBox::SetPosition(sf::Vector2f pos){
    text.setPosition(pos);
}

void TextBox::SetFont(sf::Font& font){
    text.setFont(font);
}

string TextBox::get_Text(){
    return txt_strm.str();
}

void TextBox::draw_to_window(sf::RenderWindow &window){
    window.draw(text);
}

void  TextBox::Type_in(sf::Event input){
    int char_typed = input.text.unicode;
    if(char_typed < 128){
        if(txt_strm.str().length() < limit || char_typed == DELETE_KEY){
            input_text(char_typed );
        }
    }
}



void TextBox::input_text(int char_size){
    if(char_size != DELETE_KEY && char_size != ENTER_KEY){
        txt_strm << static_cast<char>(char_size);
    }
    else if(char_size == DELETE_KEY){
        if(txt_strm.str().length() > 0){
            delete_last_char();
        }
    }
    text.setString(txt_strm.str());
}

void TextBox::delete_last_char(){
    string str = txt_strm.str();
    if (!str.empty()) {
        str.pop_back();
        txt_strm.str("");
        txt_strm << str;
        text.setString(txt_strm.str());
    }

}


void TextBox:: empty_input(){
    txt_strm.str("");
    text.setString(txt_strm.str());

}