#pragma once
class Bomb {
private:
    sf::Sprite sprite_;
    sf::Texture texture_;

public:
    Bomb(std::string png_path="img/PNG/Lasers/laserRed15.png") {
        // Initialize bomb sprite and texture
        
        texture_.loadFromFile(png_path);
        sprite_.setTexture(texture_);
        sprite_.setScale(0.6,0.4);
    }

    ~Bomb() {
        // Destructor logic, if needed
    }

    sf::Sprite& getSprite() {
        return sprite_;
    }
    void Destroyed(){
	sprite_.setPosition(-1000,1000);
}
    void setSpritePosition(float x, float y) {
        sprite_.setPosition(x, y);
    }

    // Other Bomb related functions
};

