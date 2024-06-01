#include "Addon.h"

void Addon::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::Sprite Addon::getSprite() const {
    return sprite;
}
