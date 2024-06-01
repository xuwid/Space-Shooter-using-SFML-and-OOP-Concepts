#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Addon.h"
#include "LivesAddon.h"
#include "DangerAddon.h"
#include "FireAddon.h"
#include "Powerup.h"
class Player {
public:
    Player(std::string png_path, std::string png_path_left_tilt, std::string png_path_right_tilt);
    ~Player();
    void fire();
    void move(std::string s);
    void update(float deltaTime);
    void Destroyed(int x=-1000,int y=-1000);
    sf::Sprite getSprite() const;
    Bullet* getBullet(int i) const;
    int getmaxbullets();
	Bullet* bullets_[5];
	int getLives();
	void Livesplus(){
		lives=lives+1;
	}
	 void spawnLivesAddon();
        void setFireAddon(bool flag=true){
        	isFireAddonActive_=flag;	
        	}
      
      
     bool getfireaddonactive(){
     	return isFireAddonActive_;
     }
     void setPowerup(bool flag=true){
        	Powerupactive=flag;	
        }
      
      
     bool getPowerup(){
     	return Powerupactive;
     }
     int getScore(){
	return score_;
	}
	void setScore(int s){
		score_=s;
	}
Addon* addon = nullptr;
private:
float powertimer;	
bool Powerupactive;
int score_;
float fireAddonTimer_;
bool isFireAddonActive_;
	sf::Texture fireBulletTexture_;
	sf::Texture defaultBulletTexture_;
    int lives;
    sf::Sprite sprite;
    sf::Texture tex[3];
    int texIndex;
    float speed = 1;
    int x, y;
    int width, height;
    
    int num_bullets_;
    bool is_firing_;
    const int max_bullets_ = 5;

    void wraparound();
};
