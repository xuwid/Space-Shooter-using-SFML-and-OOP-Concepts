#include "enemy.h"
#pragma once

class Monster : public Enemy {
private:
    bool movingLeft_;
    sf::Clock bombDropClock_;

public:
    Monster(float x, float y)
        : Enemy("img/monster.png") {
        sprite_.setPosition(x, y);
        movingLeft_ = true;
        type_ = "Monster";
        sprite_.setScale(0.25, 0.25);
        bombDropClock_.restart();
    }

    void update(float time, float screenHeight,const sf::Sprite& playerSprite) override {
        float monsterSpeed = 80.0f;
        float movementX = 0.0f;

        if (sprite_.getPosition().y > screenHeight) {
            return;
        }

        if (movingLeft_) {
            movementX = -monsterSpeed * time;
            if (sprite_.getPosition().x <= 0.0f) {
                movingLeft_ = false;
            }
        } else {
            movementX = monsterSpeed * time;
            float rightEdge = screenHeight - sprite_.getGlobalBounds().width;
            if (sprite_.getPosition().x >= rightEdge) {
                movingLeft_ = true;
            }
        }

        sprite_.move(movementX, 0.0f);

        if (bombDropClock_.getElapsedTime().asSeconds() > 3.5f) {
            dropBomb();
            bombDropClock_.restart();
        }

        // Update bomb position if it exists
        if (bomb_ != nullptr) {
            float bombSpeed = 80.0f; // Adjust the bomb speed as needed
            float bombMovementX = movementX; // Horizontal movement
            float bombMovementY = bombSpeed * time; // Vertical movement

            bomb_->getSprite().setScale(1, 14);
            bomb_->getSprite().move(bombMovementX, 0);

            // Destroy the bomb after 1.5 seconds
            if (clock_.getElapsedTime().asSeconds() > 1.5f) {
                delete bomb_; // Destroy the bomb
                bomb_ = nullptr; // Set bomb pointer to nullptr
            } else {
                // Check if the tip of the bomb reaches the bottom of the screen
                float desiredPositionY = screenHeight;
                if (bomb_->getSprite().getPosition().y >= desiredPositionY) {
                    delete bomb_; // Destroy the bomb
                    bomb_ = nullptr; // Set bomb pointer to nullptr
                }
            }
        }
    }
};

