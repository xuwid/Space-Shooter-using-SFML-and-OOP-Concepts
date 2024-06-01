	#pragma once
#include "Addon.h"

class Powerup : public Addon {
public:
    Powerup(float startX, float startY);

    void update(float deltaTime) override;

    std::string getType() const override;
};
