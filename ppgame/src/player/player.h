#ifndef PLAYER_H
#define PLAYER_H

#include <scene/2d/physics_body_2d.h>

class FiniteStateMachine;
class AnimatedSprite2D;

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

	// setting
	void set_finite_state_machine(FiniteStateMachine* p_fsm);
	FiniteStateMachine* get_finite_state_machine() const;
	void set_anim_sprite(AnimatedSprite2D* p_animSprite);
	AnimatedSprite2D* get_anim_sprite() const;

	// nodes
	FiniteStateMachine* fsm = nullptr;
	AnimatedSprite2D* anim_sprite = nullptr;
};

#endif // PLAYER_H
