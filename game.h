#pragma once

#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <fstream>
#include "player.h"
#include "enemy.h"
#include "alphainvader.h"
#include "betainvader.h"
#include "gammainvader.h"
#include "monster.h"
#include <sstream>
#include <iomanip>
#include "dragon.h"
#include "Addon.h"
#include "Playerdata.h"
#include "pausemenu.h"
class Game {
public:
   const static int MAX_HIGHSCORES = 5;
    PlayerData highscores_[MAX_HIGHSCORES];
    //x	int score_ = 0;
    int level = 1;
    sf::Font font_;
    PlayerData previousPlayer_;

    // Load highscores from file
    void showHighscores();
    void saveHighscores();
    void updateHighscores(const PlayerData& currentPlayer);
    void loadHighscores();
    void sortHighscores();
    Game();
    ~Game();
    void startGame(sf::RenderWindow& window);

private:
    PauseMenu  h;
    float deltaTime=0;
    sf::Clock clock;
    bool paused_ = false;
    float timer = 0;
    sf::Text scoreText_;
    sf::Text levelText_;
    sf::Text livesText_;
    Player* p_;
    Enemy** enemies_;
    int numEnemies_;
    sf::Sprite background_;
    sf::Texture bg_texture_;
    int enemiesDestroyed = 0;
    int index = 0;
    float monsterTimer = 0;
    float dragonTimer = 0;
    int currentPattern = 1;
    bool monsterSpawned = false;
    bool dragonSpawned = false;

    void createMonsterLevel();
    void createInvadersLevel1();
    void createInvadersLevel2();
    void createInvadersLevel3();
    void createDragonLevel1();
    bool checkCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2);
};

