#include "invader.h"
class BetaInvader : public Invader {
public:
    BetaInvader(float x, float y)
        : Invader("img/PNG/Enemies/enemyGreen2.png", x, y) {
        bombDropTime_ = 3.0f;
        type_ = "Beta"; // Beta invader drops bomb every 3 seconds
    }
    
};

