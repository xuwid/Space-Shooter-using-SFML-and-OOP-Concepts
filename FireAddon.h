#pragma once
#include "Addon.h"

class FireAddon : public Addon {
public:
    FireAddon(float startX, float startY);

    void update(float deltaTime) override;

    std::string getType() const override;
};	
