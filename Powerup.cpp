#include "Powerup.h"

Powerup::Powerup(float startX, float startY) {
    texture.loadFromFile("img/PNG/Power-ups/bold_silver.png");
    sprite.setScale(1.25,1.25);
    sprite.setTexture(texture);
    x = startX;
    y = startY;
    sprite.setPosition(x, y);
}

void Powerup::update(float deltaTime) {
    // Update logic specific to Powerup
    // Move the addon downwards
    y += speed * deltaTime;
    sprite.setPosition(x, y);
}

std::string Powerup::getType() const {
    return "Powerup";
}
