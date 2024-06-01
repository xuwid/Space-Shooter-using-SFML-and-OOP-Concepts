#pragma once

#include <SFML/Graphics.hpp>

class Bullet {
public:
    Bullet();

    void fire(int x, int y);
    void move();
    void Destroyed(int x=-1000,int y=-1000);
    bool isActive() const;
    sf::Sprite getSprite() const;
    void setTexture(const sf::Texture tex){
    	sprite_.setTexture(tex);
    	
    }
private:
    sf::Sprite sprite_;
    sf::Texture texture_;
    float speed_ = 0.75;
    int x_, y_;
    int width_, height_;
    bool isActive_;
};
