#include "Player.h"
#include <cstring>

Player::Player(const char* name) {
    std::strcpy(this->name, name);
}
const char* Player::getName() const {
    return name;
}
