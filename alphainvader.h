#pragma once
#include "invader.h"
class AlphaInvader : public Invader {
public:
    AlphaInvader(float x, float y)
        : Invader("img/PNG/Enemies/enemyBlack1.png", x, y) {
        bombDropTime_ = 5.0f; 
        type_ = "Alpha";// Alpha invader drops bomb every 5 seconds
    }
 
};

