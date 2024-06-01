#pragma once
#include <SFML/Graphics.hpp>

class Addon {
public:
    virtual ~Addon() {}

    virtual void update(float deltaTime) = 0;

    void draw(sf::RenderWindow& window);

    sf::Sprite getSprite() const;

    virtual std::string getType() const = 0;

protected:
    sf::Texture texture;
    sf::Sprite sprite;
    float x;
    float y;
    float speed = 70.0f; // Adjust the speed as needed
};
