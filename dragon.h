#pragma once
#include "enemy.h"

class Dragon : public Enemy {
public:
    Dragon(float x, float y)
        : Enemy("img/dragon1.png") {
        type_ = "Dragon";
        sprite_.setPosition(x, y);
        sprite_.setScale(1.45, 1.45);
    }

    void update(float time, float screenHeight, const sf::Sprite& playerSprite) override {
        // Check if a bomb already exists
        if (bomb_ != nullptr) {
            if (bombDropTime_ <= 0.0f) {
                delete bomb_;
                bomb_ = nullptr;
            } else {
                bombDropTime_ -= time;
            }
        } else {
            if (bombCreationTime_ <= 0.0f) {
                // Determine the bomb orientation based on the player's position
                std::string bombImage = "img/downward.png";
                sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
                sf::FloatRect dragonBounds = sprite_.getGlobalBounds();
                float bombX = sprite_.getPosition().x + (sprite_.getGlobalBounds().width / 2);
                float bombY = sprite_.getPosition().y + sprite_.getGlobalBounds().height + 10.0f;

                if (playerBounds.top > dragonBounds.top) {
                    if (playerBounds.left > dragonBounds.left) {
                        bombImage = "img/right_downward.png";
                    } else if (playerBounds.left < dragonBounds.left) {
                        bombImage = "img/left_downward.png";
                        //bombX += 300.0f; // Increment x position by 300 when firing left downward
                    }
                }

                // Create a new bomb object with the determined image
                bomb_ = new Bomb(bombImage);
                bomb_->setSpritePosition(bombX, bombY);
                bomb_->getSprite().setScale(1, 3);

                // Set the bomb drop time
                bombDropTime_ = 0.5f;

                // Reset the bomb creation time
                bombCreationTime_ = 1.25f;
            } else {
                bombCreationTime_ -= time;
            }
        }
    }

private:
    float bombCreationTime_ = 0;
};

