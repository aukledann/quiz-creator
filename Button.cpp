//
// Created by annab on 12.11.2024.
//

#include "Button.h"


Button::Button(){};

bool Button:: operator <(const Button& other) const{
    return text_on_button.getString() < other.text_on_button.getString();
}

bool  Button::operator ==(const Button& other) const{
    return text_on_button.getString() == other.text_on_button.getString();
}

Button::Button(const string txt,sf::Color txt_Color, int char_size, sf::Color btn_color, sf::Vector2f size){
    text_on_button.setString(txt);
    text_on_button.setFillColor(txt_Color);
    text_on_button.setCharacterSize(char_size);

    button.setFillColor(btn_color);
    button.setSize(size);
}

void Button::SetFont(sf::Font& font){
    text_on_button.setFont(font);
}

void Button:: setPosition(sf::Vector2f pos){

    button.setPosition(pos);
    float xPos = (pos.x + button.getLocalBounds().width / 2) - (text_on_button.getLocalBounds().width) / 2;
    float yPos = (pos.y + button.getLocalBounds().height / 6)- (text_on_button.getLocalBounds().height / 2);

    text_on_button.setPosition({xPos,yPos});
}

void Button::draw_to_window(sf::RenderWindow &window){
    window.draw(button);
    window.draw(text_on_button);

}

string Button::get_text_on_btn(){
    return text_on_button.getString();
}

sf::Color Button::get_color(){
    return button.getFillColor();
}


bool Button::mouse_over_button(sf::RenderWindow &window){
    float mouse_posX = sf::Mouse::getPosition(window).x;
    float mouse_posY = sf::Mouse::getPosition(window).y;

    float btn_posX_left = button.getPosition().x;
    float btn_posY_top = button.getPosition().y;

    float btn_posX_right = button.getPosition().x + button.getLocalBounds().width;
    float btn_posY_bottom = button.getPosition().y + button.getLocalBounds().height;

    if(mouse_posX > btn_posX_left && mouse_posX < btn_posX_right && mouse_posY > btn_posY_top && mouse_posY < btn_posY_bottom){
        return true;//if mouse is within button area
    }
    else{
        return false;
    }

}


void Button:: change_btn_col(sf::Color color){
    button.setFillColor(color);
}

void Button:: reuse_btn(string txt,sf::Color txt_Color, int char_size, sf::Color btn_color, sf::Vector2f size){
    text_on_button.setString(txt);
    text_on_button.setFillColor(txt_Color);
    text_on_button.setCharacterSize(char_size);

    button.setFillColor(btn_color);
    button.setSize(size);
}
