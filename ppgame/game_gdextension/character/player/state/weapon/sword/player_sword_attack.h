#ifndef PLAYER_SWORD_ATTACK_H
#define PLAYER_SWORD_ATTACK_H

#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/string_name.hpp>
using namespace godot;

#include "character/player/state/player_state.h"

//! 玩家剑攻击状态
class PlayerSwordAttack : public PlayerState {
	GDCLASS(PlayerSwordAttack, PlayerState)

public:
	virtual void enter() override;
	virtual StringName on_process(double delta) override;
	virtual void on_physics_process(double delta) override;
	virtual StringName on_input(int p_fsm_input, const Variant& p_variant) override;
	virtual void exit() override;

public:
	PlayerSwordAttack() {}

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_SWORD_ATTACK_H
