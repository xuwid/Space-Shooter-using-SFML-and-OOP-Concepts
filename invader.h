#pragma once
#include "enemy.h"
class Invader : public Enemy {
public:
    Invader(const std::string& imgPath, float x, float y)
        : Enemy(imgPath) {
        sprite_.setPosition(x, y);
    }
   void update(float time, float height,const sf::Sprite& playerSprite) override{
    if (clock_.getElapsedTime().asSeconds() > bombDropTime_) {
        dropBomb();
        clock_.restart();
    }
    
    // Update bomb position if it exists
    if (bomb_ != nullptr) {
        float bombSpeed = 35.f; // Adjust the bomb speed as needed
        float bombMovementX = 0.0f; // No horizontal movement
        float bombMovementY = bombSpeed * time; // Vertical movement
        bomb_->getSprite().move(bombMovementX, bombMovementY);

        // Check if the bomb reaches the bottom of the screen
        float desiredPositionY = height + bomb_->getSprite().getGlobalBounds().height;
        if (bomb_->getSprite().getPosition().y >= desiredPositionY) {
            delete bomb_; // Destroy the bomb
            bomb_ = nullptr; // Set bomb pointer to nullptr
        }
    }
    }
    
   
		
};

