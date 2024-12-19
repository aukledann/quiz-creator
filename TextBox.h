//
// Created by annab on 12.11.2024.
//

#ifndef TEST_WINDOW_TEXTBOX_H
#define TEST_WINDOW_TEXTBOX_H
#include <SFML/Graphics.hpp>
#include<iostream>
#include<sstream>

using namespace std;
#define DELETE_KEY 8
#define ENTER_KEY 13


class TextBox {
    sf::Text text;
    int limit;
    ostringstream txt_strm;

    void input_text(int char_size);
    void delete_last_char();

public:


    void SetFont(sf::Font& font);
    void SetText(string str);
    void SetLimit(int lim);
    void SetPosition(sf::Vector2f pos);
    string get_Text();
    void draw_to_window(sf::RenderWindow &window);
    void empty_input();


    void Type_in(sf::Event input);

    TextBox();
    TextBox(int size, sf::Color color);
    TextBox(const TextBox& other);
    TextBox(TextBox&& other);



};


#endif //TEST_WINDOW_TEXTBOX_H
