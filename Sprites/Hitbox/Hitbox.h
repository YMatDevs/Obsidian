//
// Created by Win 11 on 21-07-2025.
//

#ifndef HITBOX_H
#define HITBOX_H
#include <vector>

#include "../Asteroid/Asteroid.h"
#include "../Player/Player.h"

struct Hitbox {
  Asteroid* asteroid;
};

inline void checkCollision() {

}

inline std::vector<Hitbox> hitboxes;

#endif //HITBOX_H
