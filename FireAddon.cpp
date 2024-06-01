#include "FireAddon.h"

FireAddon::FireAddon(float startX, float startY) {
    texture.loadFromFile("img/PNG/Power-ups/things_bronze.png");
    sprite.setScale(1.25,1.25);
    sprite.setTexture(texture);
    x = startX;
    y = startY;
    sprite.setPosition(x, y);
}

void FireAddon::update(float deltaTime) {
    // Update logic specific to FireAddon
    // Move the addon downwards
    y += speed * deltaTime;
    sprite.setPosition(x, y);
}

std::string FireAddon::getType() const {
    return "FireAddon";
}
