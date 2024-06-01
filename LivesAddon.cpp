#include "LivesAddon.h"

LivesAddon::LivesAddon(float startX, float startY) {
    texture.loadFromFile("img/PNG/Power-ups/powerupRed_star.png");
    sprite.setTexture(texture);
    x = startX;
    y = startY;
    sprite.setPosition(x, y);
}

void LivesAddon::update(float deltaTime) {
    // Update logic specific to LivesAddon
    // Move the addon downwards
    y += speed * deltaTime;
    sprite.setPosition(x, y);
}

std::string LivesAddon::getType() const {
    return "LivesAddon";
}
