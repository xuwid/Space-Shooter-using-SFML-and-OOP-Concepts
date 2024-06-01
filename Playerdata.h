#pragma once
class PlayerData {
 	public:
    std::string name;
    int score;
    std::string badge;

    PlayerData() {
        name = "";
        score = 0;
        badge = "";
    }
};

