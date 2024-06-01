#pragma once
#include "invader.h"
class GammaInvader : public Invader {
public:
    GammaInvader(float x, float y)
        : Invader("img/PNG/Enemies/enemyRed3.png", x, y) {
        bombDropTime_ = 2.0f;
        type_ = "Gamma"; // Gamma invader drops bomb every 2 seconds
    }
  
};

