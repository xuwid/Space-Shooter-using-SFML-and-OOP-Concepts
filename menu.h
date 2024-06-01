#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include "game.h"

class Menu {
public:
    // Default constructor
    Menu();

    void run();

private:
 bool menu_open ;
    int selected_option;

    sf::RenderWindow window_;

    sf::Font font_;
    std::string options_[4];
    sf::Text option_texts_[4];

    sf::Texture bg_texture_;
    sf::Sprite bg_sprite_;
	void displayInfo();
    void handleEvents();
    void draw();
};
#endif

