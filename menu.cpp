#include "menu.h"

Menu::Menu() : window_(sf::VideoMode(700, 700), "My Game") {
	menu_open=true;
	selected_option=0;
    // Set up font
    if (!font_.loadFromFile("Calibri.ttf")) {
        // Handle error
    }

    // Set up menu options
    options_[0] = "Start Game";
    options_[1] = "Highscores";
    options_[2] = "Info";
    options_[3] = "Exit";

    // Set up menu text
    for (int i = 0; i < 4; i++) {
        option_texts_[i].setString(options_[i]);
        option_texts_[i].setFont(font_);
        option_texts_[i].setCharacterSize(36);
        option_texts_[i].setOrigin(option_texts_[i].getLocalBounds().width / 2.f, option_texts_[i].getLocalBounds().height / 2.f);
        option_texts_[i].setPosition(350.f, 200.f + i * 50.f);
        if (i == 0) {
            option_texts_[i].setFillColor(sf::Color::Red);
        }
    }

    // Set up background
    if (!bg_texture_.loadFromFile("background.png")) {
        // Handle error
    }
    bg_sprite_.setTexture(bg_texture_);
}

void Menu::run() {
   
    while (menu_open) {
        handleEvents();
        draw();
    }
}

void Menu::handleEvents() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window_.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                if (selected_option > 0) {
                    option_texts_[selected_option].setFillColor(sf::Color::White);
                    selected_option--;
                    option_texts_[selected_option].setFillColor(sf::Color::Red);
                }
            }
            if (event.key.code == sf::Keyboard::Down) {
                if (selected_option < 3) {
                    option_texts_[selected_option].setFillColor(sf::Color::White);
                    selected_option++;
                    option_texts_[selected_option].setFillColor(sf::Color::Red);
                }
            }
            if (event.key.code == sf::Keyboard::Return) {
                Game g;
                if (selected_option == 0) {
                    // Start game
                    g.startGame(window_); // Pass the window to the game
                } else if (selected_option == 1) {
                    // Show highscores
                    g.showHighscores();
                } else if (selected_option == 2) {
                    // Show info
                    displayInfo();
                } else if (selected_option == 3) {
                    // Quit
                    window_.close();
                }
            }
        }
    }
}

void Menu::draw() {
    window_.clear();
    window_.draw(bg_sprite_);

    for (int i = 0; i < 4; i++) {
        window_.  draw(option_texts_[i]);
    }

    window_.display();
}
void Menu::displayInfo() {
    // Set up info text
    sf::Text info_text;
    info_text.setString("USE ARROW KEYS TO MOVE \n AND PRESS SPACE TO FIRE");
    info_text.setFont(font_);
    info_text.setCharacterSize(36);
    info_text.setFillColor(sf::Color::Blue);
    info_text.setOrigin(info_text.getLocalBounds().width / 2.f, info_text.getLocalBounds().height / 2.f);
    info_text.setPosition(350.f, 350.f);

    // Draw info text and display it
    window_.clear();
    window_.draw(bg_sprite_);
    window_.draw(info_text);
    window_.display();

    // Wait for user to press any key to return to menu
    sf::Event event;
    while (window_.waitEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            return;
        }
    }
}
