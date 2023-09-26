#ifndef PLAYER_H
#define PLAYER_H

#include <scene/2d/physics_body_2d.h>

class Player : public CharacterBody2D {
    GDCLASS(Player, CharacterBody2D);

public:
	Player();
};

#endif // PLAYER_H