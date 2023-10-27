#ifndef PLAYER_H
#define PLAYER_H

#include <scene/2d/physics_body_2d.h>

#include "pp.h"

class AnimationPlayer;
class FiniteStateMachineComponent;
class PlayerMovementComponent;

class Player : public CharacterBody2D {
    GDCLASS(Player, CharacterBody2D);

public:
	Player();

protected:
	static void _bind_methods();
	void _notification(int p_notification);

	virtual void unhandled_input(const Ref<InputEvent> &p_event);

//~Begin This Class
private:
	void _ready();
	void _process(float deltaTime);
	void _physics_process(float deltaTime);

	// nodes
	PP_PROPERTY(AnimationPlayer*, back_arm, nullptr);
	PP_PROPERTY(AnimationPlayer*, leg, nullptr);
	PP_PROPERTY(AnimationPlayer*, torso, nullptr);
	PP_PROPERTY(AnimationPlayer*, head, nullptr);
	PP_PROPERTY(AnimationPlayer*, front_arm, nullptr);

	PP_PROPERTY(FiniteStateMachineComponent*, fsm, nullptr);
	PP_PROPERTY(PlayerMovementComponent*, movement_component, nullptr);
};

#endif // PLAYER_H
