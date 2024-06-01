#include "Bullet.h"

Bullet::Bullet()
    : isActive_(false)
{
    texture_.loadFromFile("img/PNG/Lasers/laserBlue02.png");
    sprite_.setTexture(texture_);
    x_ = 0;
    y_ = 0;
    width_ = sprite_.getGlobalBounds().width;
    height_ = sprite_.getGlobalBounds().height;
}

void Bullet::fire(int x, int y)
{
    isActive_ = true;
    x_ = x;
    y_ = y;
    sprite_.setPosition(x_ + 9, y_ + 1);
}

void Bullet::move()
{
    sprite_.move(0, -speed_);
    if (sprite_.getPosition().y < -height_ / 2) {
        isActive_ = false;
    }
}

bool Bullet::isActive() const
{
    return isActive_;
}
void Bullet::Destroyed(int x,int y){
	sprite_.setPosition(x,y);
}
sf::Sprite Bullet::getSprite() const
{
    return sprite_;
}
