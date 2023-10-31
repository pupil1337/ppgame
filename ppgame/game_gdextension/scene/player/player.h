#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/animation_player.hpp>
#include "pp.h"

using namespace godot;

class PlayerMovementFSMComponent;
class PlayerMovementComponent;

class Player : public CharacterBody2D {
    GDCLASS(Player, CharacterBody2D);

public:
	Player();

protected:
	static void _bind_methods();

public:
	virtual void _ready() override;
	virtual void _process(double delta) override;
	virtual void _physics_process(double delta) override;
	virtual void _unhandled_input(const Ref<InputEvent> &event) override;

//~Begin This Class
public:
	// nodes
	PP_PROPERTY(AnimationPlayer*, back_arm, nullptr);
	PP_PROPERTY(AnimationPlayer*, leg, nullptr);
	PP_PROPERTY(AnimationPlayer*, torso, nullptr);
	PP_PROPERTY(AnimationPlayer*, head, nullptr);
	PP_PROPERTY(AnimationPlayer*, front_arm, nullptr);

	PP_PROPERTY(PlayerMovementFSMComponent*, movement_fsm_component, nullptr);
	PP_PROPERTY(PlayerMovementComponent*, movement_component, nullptr);
};

#endif // PLAYER_H
