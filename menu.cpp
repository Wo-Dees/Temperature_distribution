//
// Created by Карим Вафин on 28.04.2021.
//

#include "menu.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Menu::Menu(sf::RenderWindow& win) : Window(win)
{
    choice = 0;
}

int Menu::run()
{
    data = load_from_file("../data.txt");
    choice = 0;
    sf::Texture background;
    if (!background.loadFromFile("../Additional/temp_dist.jpeg"))
        throw std::exception();
    backgr.setTexture(background);
    sf::Text title = create_text(250, 70, "Temperature distribution", 100, sf::Color::White);
    sf::Text text1 = create_text(325, 330, "Start", 80, sf::Color::White);
    sf::Text text2 = create_text(325, 530, "Load from file", 80, sf::Color::White);
    sf::Text text3 = create_text(345, 730, "Exit", 80, sf::Color::White);
    sf::RectangleShape button1 = create_button(290, 310, 300, 80, sf::Color::White);
    sf::RectangleShape button2 = create_button(290, 510, 300, 80, sf::Color::White);
    sf::RectangleShape button3 = create_button(290, 710, 300, 80, sf::Color::White);
    button_animation();
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        process_events();
        window.clear(sf::Color::White);
        window.draw(backgr);
        draw_objects();
        window.display();
        if (choice != 0)
            break;
    }
    return choice;
}

void Menu::process_events()
{
    sf::Vector2i m_pos = sf::Mouse::getPosition(window);
    int i = 0;
    for (int j = 0; j < buttons.size(); j++)
    {
        i++;
        sf::Vector2f b_pos = buttons[j].getPosition();
        sf::Vector2f b_size = buttons[j].getSize();
        sf::IntRect rect(b_pos.x, b_pos.y, b_size.x, b_size.y);
        if (rect.contains(m_pos))
        {
            texts[j + 1].setFillColor(sf::Color::Yellow);
            texts[j + 1].setCharacterSize(90);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                choice = i;
            }
        }
        else
        {
            texts[j + 1].setFillColor(sf::Color::White);
            texts[j + 1].setCharacterSize(80);
        }
    }
}

void Menu::button_animation()
{
    for (int i = 0; i < texts.size(); i++)
    {
        sf::Vector2f pos = texts[i].getPosition();
        texts[i].setPosition(-500, pos.y);
        while (texts[i].getPosition().x < pos.x)
        {
            sf::Event event;

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            texts[i].move(100, 0);
            window.clear(sf::Color::White);
            window.draw(backgr);
            for (int k = 0; k <= i; k++)
                window.draw(texts[k]);
            window.display();
        }
        sf::Vector2f new_pos = texts[i].getPosition();
        for (int j = 0; j < int(abs(pos.x - new_pos.x)) / 20; j++)
        {
            texts[i].move(-20, 0);
            window.clear(sf::Color::White);
            window.draw(backgr);
            for (int k = 0; k <= i; k++)
                window.draw(texts[k]);
            window.display();
        }
    }
}

void Menu::draw_objects()
{
    for (auto& btn : buttons)
        window.draw(btn);
    window.draw(backgr);
    for (auto& txt : texts)
        window.draw(txt);
}

std::vector<double> Menu::str_to_vec(std::string s)
{
    std::string::size_type sz;
    std::vector<std::string> vec;
    std::vector<double> ans;
    std::string word;
    std::stringstream str(s);
    while (str >> word)
    {
        double a = stod(word, &sz);
        ans.push_back(a);
    }
    return ans;
}

std::queue<std::vector<double >> Menu::load_from_file(std::string file_name)
{
    std::queue<std::vector<double >> answer;
    std::string buff;
    std::ifstream in("../data.txt");
    std::vector<double> part;
    if (in.is_open()) {
        for (int i = 0; i < 50000; i++)
        {
            getline(in, buff);
            std::vector<double> vec = str_to_vec(buff);
            for(auto i: vec)
                part.push_back(i);
            if (part.size() == 2500)
            {
                answer.push(part);
                part.clear();
            }
        }
    }
    in.close();
    return answer;
}