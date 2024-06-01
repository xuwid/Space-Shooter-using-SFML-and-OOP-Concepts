#include "game.h"
#include <SFML/Graphics.hpp>
#include <time.h>

void Game::showHighscores() {
    std::ifstream file("highscores.txt");
    if (file.is_open()) {
        sf::Font font;
        if (!font.loadFromFile("Calibri.ttf")) {
            // Handle error loading font
            return;
        }

        sf::Text highscoreText;
        highscoreText.setFont(font);
        highscoreText.setCharacterSize(24);
        highscoreText.setPosition(175.f, 300.f); // Adjusted position

        sf::Text columnHeaderText;
        columnHeaderText.setFont(font);
        columnHeaderText.setCharacterSize(35);
        columnHeaderText.setPosition(175.f, 250.f);

        sf::Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile("background.png")) {
            // Handle error loading background image
            return;
        }
        sf::Sprite backgroundSprite(backgroundTexture);

        sf::RenderWindow highscoreWindow(sf::VideoMode(700, 700), "Highscores");

        std::string columnHeaderString = "Name      Score       Badge";

        // Read the column headers
        columnHeaderText.setString(columnHeaderString);

        std::string line;
        std::string highscoreString;
        int count = 0;

        // Read the highscores from the file and store the top 3
        while (std::getline(file, line) && count < 3) {
            std::istringstream iss(line);
            std::string name, score, badge;
            if (iss >> name >> score >> badge) {
                highscoreString += name + "\t\t\t" + score + "\t\t\t" + badge + "\n";
                count++;
            }
        }

        // Set the text for highscore text
        highscoreText.setString(highscoreString);

        file.close();

        while (highscoreWindow.isOpen()) {
            sf::Event event;
            while (highscoreWindow.pollEvent(event)) {
                                if (event.type == sf::Event::Closed) {
                    highscoreWindow.close();
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        highscoreWindow.close();
                    }
                }
            }

            highscoreWindow.clear();
            highscoreWindow.draw(backgroundSprite);
            highscoreWindow.draw(columnHeaderText);
            highscoreWindow.draw(highscoreText);
            highscoreWindow.display();
        }
    }
}
void Game::createDragonLevel1() {
    enemies_[index] = new Dragon(200, 0);

    enemies_[index]->dropBomb();  // Call dropBomb() for the Dragon enemy
}

void Game::saveHighscores() {
    std::ofstream file("highscores.txt");
    if (file.is_open()) {
        // Calculate maximum length of name and score fields
        int maxNameLength = 0;
        int maxScoreLength = 0;
        for (int i = 0; i < MAX_HIGHSCORES; ++i) {
            int nameLength = highscores_[i].name.length();
            int scoreLength = std::to_string(highscores_[i].score).length();
            if (nameLength > maxNameLength) {
                maxNameLength = nameLength;
            }
            if (scoreLength > maxScoreLength) {
                maxScoreLength = scoreLength;
            }
        }

        // Set width for columns
        const int columnWidth = maxNameLength + 4;  // Add 4 for extra spacing
        const int scoreColumnWidth = maxScoreLength + 4;

        for (int i = 0; i < MAX_HIGHSCORES; ++i) {
            file << std::left << std::setw(columnWidth) << highscores_[i].name;
            file << std::setw(scoreColumnWidth) << highscores_[i].score;
            file << std::setw(columnWidth) << highscores_[i].badge << "\n";
        }
        file.close();
    }
}

void Game::updateHighscores(const PlayerData& currentPlayer) {
    int insertIndex = -1;
    for (int i = 0; i < MAX_HIGHSCORES; ++i) {
        if (currentPlayer.score > highscores_[i].score) {
            insertIndex = i;
            break;
        }
    }

    if (insertIndex != -1) {
        for (int i = MAX_HIGHSCORES - 1; i > insertIndex; --i) {
            highscores_[i] = highscores_[i - 1];
        }
        highscores_[insertIndex] = currentPlayer;
    }

    // Assign badges based on position in highscores
    for (int i = 0; i < MAX_HIGHSCORES; ++i) {
        if (i == 0) {
            highscores_[i].badge = "Gold";
        } else if (i == 1) {
            highscores_[i].badge = "Silver";
        } else if (i == 2) {
            highscores_[i].badge = "Bronze";
        } else {
            highscores_[i].badge = "No Badge";
        }
    }

    saveHighscores();
}

void Game::loadHighscores() {
    std::ifstream file("highscores.txt");
    if (file.is_open()) {
        for (int i = 0; i < MAX_HIGHSCORES; ++i) {
            file >> highscores_[i].name >> highscores_[i].score >> highscores_[i].badge;
        }
        file.close();
    }
}

void Game::sortHighscores() {
    for (int i = 0; i < MAX_HIGHSCORES - 1; ++i) {
        for (int j = i + 1; j < MAX_HIGHSCORES; ++j) {
            if (highscores_[i].score < highscores_[j].score) {
                // Swap the positions of highscores if the score is in descending order
                PlayerData temp = highscores_[i];
                highscores_[i] = highscores_[j];
                highscores_[j] = temp;
            }
        }
    }
}


Game::Game()
    : p_(new Player("img/player_ship.png", "img/player_shipleft.png", "img/player_shipright.png")),
      numEnemies_(30), font_()
{
    if (!font_.loadFromFile("Calibri.ttf")) {
        std::cout << "Failed to load font." << std::endl;
    }

    // Set up score text
    scoreText_.setFont(font_);
    scoreText_.setCharacterSize(20);
    scoreText_.setFillColor(sf::Color::White);
    scoreText_.setPosition(10, 10);

    // Set up level text
    levelText_.setFont(font_);
    levelText_.setCharacterSize(20);
    levelText_.setFillColor(sf::Color::White);
    levelText_.setPosition(10, 40);

    // Set up lives text
    livesText_.setFont(font_);
    livesText_.setCharacterSize(20);
    livesText_.setFillColor(sf::Color::White);
    livesText_.setPosition(10, 70);

    bg_texture_.loadFromFile("img/background.jpg");
    background_.setTexture(bg_texture_);
    background_.setScale(2, 1.5);

    // Initialize enemies array
    enemies_ = new Enemy*[numEnemies_];
    for (int i = 0; i < numEnemies_; i++) {
        enemies_[i] = nullptr;
    }
}

Game::~Game()
{
    delete p_;
    for (int i = 0; i < numEnemies_; i++) {
        delete enemies_[i];
    }
    delete[] enemies_;
}

void Game::createMonsterLevel() {
        enemies_[index] = new Monster(0, 0);
        
      //  index++;
        
    }



void Game::createInvadersLevel1() {
    while (index < 3) {
        enemies_[index] = new AlphaInvader(100, index * 150);
        index++;
    }
    enemies_[index] = new BetaInvader(300, 1);
    index++;
    enemies_[index] = new BetaInvader(500, 0);
    index++;
    enemies_[index] = new GammaInvader(500, 150);
    index++;
    enemies_[index] = new GammaInvader(500, 300);
    index++;
    enemies_[index] = new BetaInvader(300, 300);
    index++;

    // Scale down the enemies' sprites
    for (int i = 0; i < numEnemies_; i++) {
        if (enemies_[i] != nullptr) {
            enemies_[i]->getSprite().setScale(0.5f, 0.5f);
        }
    }
}
void Game::createInvadersLevel2() {
    index = 0;
    while (index < 3) {
        enemies_[index] = new GammaInvader((100) + index * 200, 300);
        index++;
    }
    enemies_[index] = new BetaInvader(300, 0);
    index++;
    enemies_[index] = new AlphaInvader(200, 150);
    index++;
    enemies_[index] = new GammaInvader(400, 150);
    index++;

    // Scale down the enemies' sprites
    for (int i = 0; i < numEnemies_; i++) {
        if (enemies_[i] != nullptr) {
            enemies_[i]->getSprite().setScale(0.5f, 0.5f);
        }
    }
}
void Game::createInvadersLevel3() {
    index = 0;
    while (index < 4) {
        enemies_[index] = new GammaInvader(100 + 150 * index, index * 150);
        index++;
    }
    while (index < 8) {
        enemies_[index] = new BetaInvader(600 - 150 * (index - 4), (index - 4) * 150);
        index++;
    }
    for (int i = 0; i < numEnemies_; i++) {
        if (enemies_[i] != nullptr) {
            enemies_[i]->getSprite().setScale(0.5f, 0.5f);
        }
    }
}


bool Game::checkCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2) {
    sf::FloatRect rect1 = sprite1.getGlobalBounds();
    sf::FloatRect rect2 = sprite2.getGlobalBounds();

    return rect1.left < rect2.left + rect2.width &&
           rect1.left + rect1.width > rect2.left &&
           rect1.top < rect2.top + rect2.height &&
           rect1.top + rect1.height > rect2.top;
}

void Game::startGame(sf::RenderWindow& window)
{
	int currentPattern = 1;
	bool monsterSpawned = false;
	bool dragonSpawned = false;
	//LivesAddon* addon = nullptr;
    float addonTimer = 0.0f;
    const float addonSpawnTime = 10.0f;

    bool paused = false;
    //PauseMenu pauseMenu(window.getSize().x, window.getSize().y);	
    clock.restart(); // Restart the clock at the beginning of the game
	createInvadersLevel1();
    while (window.isOpen()) {
        float time = clock.restart().asSeconds();
        timer += time;
	
        // Handle events
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window.close();
            }
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Space) {
                    p_->fire();
               }
                if (e.key.code == sf::Keyboard::P) {
                	
                        paused = !paused;
            		h.displayMenu(window,paused);
        	}
                
            }
        }
	
	addonTimer += time;
        if (addonTimer >= addonSpawnTime) {
            p_->spawnLivesAddon();
            addonTimer = 0.0f;
        }
        if(!paused){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            p_->move("l");
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            p_->move("r");
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            p_->move("u");
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            p_->move("d");
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            p_->move("ul");
        } // Player will move up and left diagonally
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            p_->move("ur");
        } // Player will move up and right diagonally

        // Update game objects
        p_->update(time);
        if (p_->getLives() <= 0) {
            std::cout << "Your score is " << p_->getScore() << "\n";
	    // Display the game over screen
        
            
            h.showGameOverScreen(window, p_->getScore());

            // Prompt for player's name
            std::string playerName;
            std::cout << "Enter your name: ";
            std::cin >> playerName;

            // Create PlayerData struct for the current player
            PlayerData currentPlayer;
            currentPlayer.name = playerName;
            currentPlayer.score = p_->getScore();
            currentPlayer.badge = "";

            // Load and sort the highscores
            loadHighscores();
            sortHighscores();
            updateHighscores(currentPlayer);
	
            // Close the window or take other necessary actions
            window.close();
            //window.close();
        }
	  
        if (currentPattern == 1 && enemiesDestroyed == index) {
        p_->getSprite().setPosition(250,500);
        createInvadersLevel2();
        enemiesDestroyed=0;
        currentPattern = 2;
    }
    else if (currentPattern == 2 && enemiesDestroyed == index) {
    	 p_->getSprite().setPosition(250,500);
        createInvadersLevel3();
        currentPattern = 3;
        enemiesDestroyed=0;
    }
    else if (currentPattern == 3 && enemiesDestroyed == index) {
        if (!monsterSpawned) {
         p_->getSprite().setPosition(250,500);
            createMonsterLevel();
            monsterSpawned = true;
             deltaTime = clock.restart().asSeconds();
             currentPattern=4;
        	    
        }
    }
    
    
        
    
    
    else if (monsterSpawned && monsterTimer >= 2000.0) {
    static int w=1;
    	if(w==1){
        delete enemies_[index];
        enemies_[index] = nullptr;
        monsterSpawned = false;
        p_->setScore (p_->getScore()+level * 40);
        
        dragonSpawned = true;
        w++;
         p_->getSprite().setPosition(250,500);
        enemies_[index]=new Dragon(200,0);
        }
        
    }	
   
    else if (dragonSpawned && monsterTimer >= 3000.0) {
    	static int l=1;
    	if(l==1){
        delete enemies_[index];
        enemies_[index] = nullptr;
        dragonSpawned = false;
        p_->setScore (p_->getScore()+level * 50);
        l++;
        }
    }
    	monsterTimer += deltaTime;
	//std::cout<<monsterTimer<<"\n";
        // Update enemies and check collision
        for (int i = 0; i < numEnemies_; i++) {
            if (enemies_[i] != nullptr) {
                enemies_[i]->update(time, window.getSize().y,p_->getSprite());


                if (checkCollision(p_->getSprite(), enemies_[i]->getSprite())) {
                	if(p_->getPowerup()==false)
                    	p_->Destroyed();
                }

                for (int j = 0; j < p_->getmaxbullets(); j++) {
		                    if (p_->getBullet(j)->isActive() && checkCollision(p_->getBullet(j)->getSprite(), enemies_[i]->getSprite())) {
		        if(p_->getfireaddonactive()==false){
                        p_->getBullet(j)->Destroyed();
                        }
                        std::string enemyType = enemies_[i]->getType();
                        if (enemyType == "Alpha") {
                            p_->setScore (p_->getScore()+level * 10);
                            enemiesDestroyed++;
                            enemies_[i]->Destroyed(); // Increment score for destroying Alpha Invader
                        }
                        if (enemyType == "Beta") {
                            p_->setScore (p_->getScore()+level * 20) ;
                            enemiesDestroyed++;
                           enemies_[i]->Destroyed(); // Increment score for destroying Beta Invader
                        }
                        if (enemyType == "Gamma") {
                            enemies_[i]->Destroyed();
                            enemiesDestroyed++;
                            p_->setScore (p_->getScore()+level * 30); // Increment score for destroying Gamma Invader
                        }
                        if (enemyType == "Monster") {
                            //score_ += level * 50; // Increment score for destroying Monster
                        }
                        
                    }
                }

                Bomb* bomb = enemies_[i]->getBomb();
                if (bomb != nullptr) {
                    if (checkCollision(p_->getSprite(), bomb->getSprite())) {
                    	if(p_->getPowerup()==false)
                        p_->Destroyed();
                    }
             
                    window.draw(bomb->getSprite());
                }

                
            }
        }

}
        if (enemies_[index] != nullptr && checkCollision(p_->getSprite(), enemies_[index]->getSprite())) {
           if(p_->getPowerup()==false)
           	 p_->Destroyed();
        }
	if (p_->addon != nullptr) {
            p_->addon->update(time);
		if (p_->addon->getType() == "DangerAddon" && p_->addon->getSprite().getPosition().y >= window.getSize().y) {
    		p_->setScore(p_->getScore() + level * 5 ); // Increment score by 5 when DangerAddon touches the bottom
    			
    		}
            // Check collision between player and addon
            if (checkCollision(p_->getSprite(), p_->addon->getSprite())) {
                // Perform actions when player collides with the addon
                // For example, increment lives
                if(p_->addon->getType()=="LivesAddon")
                p_->Livesplus();
		if(p_->addon->getType()=="DangerAddon")
                p_->Destroyed();
                if(p_->addon->getType()=="FireAddon")
                p_->setFireAddon();
		if(p_->addon->getType()=="Powerup")
                p_->setPowerup();
                // Remove the addon
                delete p_->addon;
                p_->addon = nullptr;
            }
        }
        window.clear(sf::Color::Black);
        window.draw(background_);
        window.draw(p_->getSprite());

        std::stringstream scoreStream;
        scoreStream << "Score: " << p_->getScore();
        scoreText_.setString(scoreStream.str());
        window.draw(scoreText_);

        std::stringstream levelStream;
        levelStream << "Level: " << level;
        levelText_.setString(levelStream.str());
        window.draw(levelText_);

        std::stringstream livesStream;
        livesStream << "Lives: " << p_->getLives();
        livesText_.setString(livesStream.str());
        window.draw(livesText_);

        for (int i = 0; i < p_->getmaxbullets(); i++) {
            if (p_->getBullet(i)->isActive()) {
                window.draw(p_->getBullet(i)->getSprite());
            }
        }
	if (p_->addon != nullptr) {
            window.draw(p_->addon->getSprite());
        }
        for (int i = 0; i < numEnemies_; i++) {
            if (enemies_[i] != nullptr) {
                window.draw(enemies_[i]->getSprite());

                Bomb* bomb = enemies_[i]->getBomb();
                if (bomb != nullptr) {
                    window.draw(bomb->getSprite());
                }
            }
        }

        window.display();
    }
}



