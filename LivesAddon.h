#pragma once
#include "Addon.h"

class LivesAddon : public Addon {
public:
    LivesAddon(float startX, float startY);

    void update(float deltaTime) override;

    std::string getType() const override;
};
