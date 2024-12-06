//
// Created by annab on 12.11.2024.
//

#ifndef TEST_WINDOW_BUTTON_H
#define TEST_WINDOW_BUTTON_H
#include <SFML/Graphics.hpp>
#include<iostream>
using namespace std;

class Button {

    sf::RectangleShape button;
    sf::Text text_on_button;
    string str;

public:
    Button();
    bool operator <(const Button& other) const;
    bool operator ==(const Button& other) const;
    Button(string txt,sf::Color txt_Color, int char_size, sf::Color btn_color, sf::Vector2f size);
    void SetFont(sf::Font &font);

    void setPosition(sf::Vector2f pos);
    void draw_to_window(sf::RenderWindow &window);
    bool mouse_over_button(sf::RenderWindow &window);
    void change_btn_col(sf::Color color);


    void reuse_btn(string txt,sf::Color txt_Color, int char_size, sf::Color btn_color, sf::Vector2f size);

    string get_text_on_btn();
    sf::Color get_color();
};


#endif //TEST_WINDOW_BUTTON_H
