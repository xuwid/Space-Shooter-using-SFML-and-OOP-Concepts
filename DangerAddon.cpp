#include "DangerAddon.h"

DangerAddon::DangerAddon(float startX, float startY) {
    texture.loadFromFile("img/PNG/Meteors/meteorGrey_med1.png");
    sprite.setTexture(texture);
    x = startX;
    y = startY;
    sprite.setPosition(x, y);
}

void DangerAddon::update(float deltaTime) {
    // Update logic specific to DangerAddon
    // Move the addon downwards
    y += speed * deltaTime;
    sprite.setPosition(x, y);
}

std::string DangerAddon::getType() const {
    return "DangerAddon";
}
