//
// Created by Карим Вафин on 28.04.2021.
//

#include "GUI.h"
#include "animation.h"
#include "menu.h"

GUI::GUI(std::queue<std::vector<double>>& data)
{
    this->data = data;
}

void GUI::run()
{
    sf::RenderWindow window (sf::VideoMode(1000, 1000), "Temperature distribution");
    window.setFramerateLimit(30);
    sf::Image icon;
    if (!icon.loadFromFile("../Additional/icon.png"))
    {
        throw std::exception();
    }
    window.setIcon(500, 500, icon.getPixelsPtr());
    Menu menu(window);
    int choice = menu.run();
    next_window(choice, window);
}

void GUI::next_window(int choice, sf::RenderWindow& window)
{
    switch (choice)
    {
        case 1:
            Animation anim(window, this->data);
            anim.run();
    }
}