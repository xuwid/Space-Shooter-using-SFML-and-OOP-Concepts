#pragma once
#include "Addon.h"

class DangerAddon : public Addon {
public:
    DangerAddon(float startX, float startY);

    void update(float deltaTime) override;

    std::string getType() const override;
};
