#include "player.h"

Player::Player(std::string png_path, std::string png_path_left_tilt, std::string png_path_right_tilt)
    : is_firing_(false), num_bullets_(0)
{
	score_=0;
	 powertimer=0;	
	 Powerupactive=false;
	 fireAddonTimer_=0;
	 isFireAddonActive_=false;

	lives=3;
    tex[0].loadFromFile(png_path);
    tex[1].loadFromFile(png_path_left_tilt);
    tex[2].loadFromFile(png_path_right_tilt);

    texIndex = 0;  // start with the default texture
    sprite.setTexture(tex[texIndex]);

    x = 340;
    y = 700;
    sprite.setPosition(x, y);
    sprite.setScale(0.75, 0.75);
    width = sprite.getGlobalBounds().width;
    height = sprite.getGlobalBounds().height;

    for (int i = 0; i < max_bullets_; i++) {
        bullets_[i] = new Bullet();
    }
    if (!fireBulletTexture_.loadFromFile("img/PNG/Lasers/laserRed01.png")) {
        // Handle error loading fire bullet texture
        return;
    }
    if (!defaultBulletTexture_.loadFromFile("img/PNG/Lasers/laserBlue02.png")) {
        // Handle error loading fire bullet texture
        return;
    }
}

Player::~Player()
{
    for (int i = 0; i < max_bullets_; i++) {
        delete bullets_[i];
    }
    delete addon;
}

void Player::fire()
{

    if (num_bullets_ >= max_bullets_) {
        return;  // limit the number of active bullets
    }
	
    
    for (int i = 0; i < max_bullets_; i++) {
        if (!bullets_[i]->isActive()) {
            bullets_[i]->fire(sprite.getPosition().x + 25, sprite.getPosition().y);
            num_bullets_++;
            break;
        }
    }
    
}

void Player::move(std::string s)
{
	
    texIndex = 0;
    sprite.setScale(0.75, 0.75);
    float delta_x = 0, delta_y = 0;
    if (s == "l") {
        delta_x = -1;
        //    texIndex = 1;  // use left tilt texture
    }
    else if (s == "r") {
        delta_x = 1;
        // texIndex = 2;  // use right tilt texture
    }
    else if (s == "u") {
        delta_y = -1;
        texIndex = 0;  // use default texture
    }
    else if (s == "d") {
        delta_y = 1;
        texIndex = 0;  // use default texture
    }
    if (s == "ul") {
        texIndex = 1;
        sprite.setScale(1, 1);
    }
    if (s == "ur") {
        texIndex = 2;
        sprite.setScale(1, 1);
    }
    delta_x *= speed;
    delta_y *= speed;

    sprite.setTexture(tex[texIndex]);  // set the texture based on movement direction
    sprite.move(delta_x, delta_y);

    wraparound();
}

void Player::update(float deltaTime)
{
    for (int i = 0; i < max_bullets_; i++) {
        if (bullets_[i]->isActive()) {
            bullets_[i]->move();
        }
        else {
            if (num_bullets_ > 0) {
                num_bullets_--;
            }
        }
    }
    if (isFireAddonActive_) {
        fireAddonTimer_ += deltaTime; // deltaTime should be a member variable or passed as a parameter to the update function

        // Check if fire addon duration exceeds 5 seconds
        if (fireAddonTimer_ >= 5.0f) {
            isFireAddonActive_ = false;
            fireAddonTimer_ = 0.0f;
        }
    }
    if (Powerupactive==true) {
        powertimer += deltaTime; // deltaTime should be a member variable or passed as a parameter to the update function

        // Check if fire addon duration exceeds 5 seconds
        if (powertimer >= 5.0f) {
            Powerupactive = false;
            powertimer = 0.0f;
        }
    }
    
}

sf::Sprite Player::getSprite() const { return sprite; }

Bullet* Player::getBullet(int i) const { return bullets_[i]; }

int Player::getmaxbullets() {
    return max_bullets_;
}

void Player::wraparound()
{
    // Wraparound horizontally
    if (sprite.getPosition().x < -width / 2) {
        sprite.setPosition(700 + width / 2, sprite.getPosition().y);
    }
    else if (sprite.getPosition().x > 700 + width / 2) {
        sprite.setPosition(-width / 2, sprite.getPosition().y);
    }

    // Wraparound vertically
    if (sprite.getPosition().y < -height / 2) {
        sprite.setPosition(sprite.getPosition().x, 700 + height / 2);
    }
    else if (sprite.getPosition().y > 700 + height / 2) {
        sprite.setPosition(sprite.getPosition().x, -height / 2);
    }
}
void  Player::Destroyed(int x,int y){

	sprite.setPosition(250,500);
	lives--;
	
}
int Player::getLives(){
	return lives;
}
void  Player::spawnLivesAddon() {
	 srand(time(NULL));
        // Spawn a LivesAddon at a random position at the top of the screen
        float startX = static_cast<float>(rand() % 700); // Adjust the range as needed
        float startY = 0.0f;
        int random=rand()%4 +1;
        //random=4;
        if(random==1){
        addon = new LivesAddon(startX, startY);
        }
        if(random==2){
        addon= new DangerAddon(startX, startY);
        }
        if(random==3){
        addon= new FireAddon(startX, startY);
        }
        if(random==4){
        addon= new Powerup(startX, startY);
        }
        }
