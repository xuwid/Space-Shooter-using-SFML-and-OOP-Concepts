#pragma once
class PauseMenu {
public:
    //PauseMenu(float width, float height);

    void showGameOverScreen(sf::RenderWindow& window, int finalScore)
{
    sf::Font font;
    if (!font.loadFromFile("Calibri.ttf")) {
        // Handle error loading font
        return;
    }

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(40);
    gameOverText.setString("Game Over");
    gameOverText.setPosition(250.f, 300.f);

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setString("Your score is: " + std::to_string(finalScore));
    scoreText.setPosition(250.f, 350.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        window.clear(sf::Color::Blue);  // Set the background color to purple
        window.draw(gameOverText);
        window.draw(scoreText);
        window.display();
    }
}

void displayMenu(sf::RenderWindow& window,bool paused_)
{
    sf::Font font_;
    sf::Text resumeText_;
	 resumeText_.setFont(font_);
    resumeText_.setCharacterSize(50);
    resumeText_.setString("Resume");
    float resumeTextPosX = (700 - resumeText_.getGlobalBounds().width) / 2;
    float resumeTextPosY = (700 - resumeText_.getGlobalBounds().height) / 2;
    resumeText_.setPosition(resumeTextPosX, resumeTextPosY);
    resumeText_.setFillColor(sf::Color::Blue);

    if (paused_) {
        window.draw(resumeText_);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
            paused_=!paused_;
        }
    }
}

	
    
};





 



