#include "bomb.h"
#pragma once
class Enemy {
protected:
    sf::Sprite sprite_;
    sf::Texture texture_;
    std::string type_; 
    Bomb* bomb_;  // Composition relationship with Bomb class
    float bombDropTime_;
    sf::Clock clock_;

public:
    Enemy(const std::string& imgPath) {
        texture_.loadFromFile(imgPath);
        sprite_.setTexture(texture_);
        bomb_ = nullptr;  // Initialize bomb to nullptr
    }

    virtual ~Enemy() {
        delete bomb_;  // Delete bomb object if it exists
    }

    std::string getType() {
        return type_;
    }

    void dropBomb() {
        // Check if a bomb already exists
        if (bomb_ != nullptr) {
            return;  // If bomb exists, skip dropping a new bomb
        }

        // Create a new bomb object
        bomb_ = new Bomb();

        // Set the position of the bomb slightly below the enemy's position
        float bombX = sprite_.getPosition().x + (sprite_.getGlobalBounds().width / 2);
        float bombY = sprite_.getPosition().y + sprite_.getGlobalBounds().height + 10.0f;

        // Set the position of the bomb sprite
        bomb_->setSpritePosition(bombX, bombY);

        // Restart the clock for bomb destruction
        clock_.restart();
    }

    virtual void update(float time, float screenHeight,const sf::Sprite& playerSprite) = 0;
    sf::Sprite& getSprite() {
        return sprite_;
    }

    void Destroyed() {
        sprite_.setPosition(-1000, 1000);
    }

    Bomb* getBomb() {
        return bomb_;
        }
   
};

