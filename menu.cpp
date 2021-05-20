//
// Created by Карим Вафин on 28.04.2021.
//

#include "menu.h"
#include <string>
#include <iostream>

Menu::Menu(sf::RenderWindow& win) : Window(win)
{
    choice = 0;
    filename = "";
}

int Menu::run()
{
    choice = 0;
    sf::Texture background;
    if (!background.loadFromFile("../Additional/background1.png"))
        throw std::runtime_error("menu.cpp");
    backgr.setTexture(background);
    start_step();
    if (choice == 1)
        init_conditions_step();
    if (choice == 2)
        load_file_step();
    return choice;
}

void Menu::start_step()
{
    sf::Text title = create_text(250, 70, "Temperature distribution", 100, sf::Color::White);
    sf::Text text1 = create_text(325, 330, "Set initial conditions", 80, sf::Color::White);
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
        draw_objects();
        window.display();
        if (choice != 0)
            break;
    }
}

// load from file
void Menu::load_file_step()
{
    choice = 2;
    texts.clear();
    buttons.clear();
    sf::Text title = create_text(250, 70, "Temperature distribution", 100, sf::Color::White);
    sf::Text text2 = create_text(325, 530, "Filename:", 80, sf::Color::White);
    sf::Text text3 = create_text(345, 730, "Exit", 80, sf::Color::White);
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
        if (choice == -1)
            window.close();
        process_events();
        window.clear(sf::Color::White);
        window.draw(backgr);
        draw_objects();
        window.display();
        if (choice == 1)
        {
            choice = 2;
            break;
        }
    }
}

void Menu::init_conditions_step()
{
    choice = 1;
}

void Menu::process_events()
{
    sf::Vector2i m_pos = sf::Mouse::getPosition(window);
    for (int j = 0; j < buttons.size(); j++)
    {
        sf::Vector2f b_pos = buttons[j].getPosition();
        sf::Vector2f b_size = buttons[j].getSize();
        sf::IntRect rect(b_pos.x, b_pos.y, b_size.x, b_size.y);
        if (rect.contains(m_pos))
        {
            texts[j + 1].setFillColor(sf::Color::Yellow);
            texts[j + 1].setCharacterSize(85);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                choice = j + 1;
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
    for (int i = 1; i < texts.size(); i++)
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

std::queue<std::vector<double>> Menu::get_data()
{
    return data;
}

const std::string &Menu::getFilename() const {
    return filename;
}

