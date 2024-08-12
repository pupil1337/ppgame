#ifndef PLAYER_WEAPON_NONE_STATE
#define PLAYER_WEAPON_NONE_STATE

#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/string_name.hpp>
using namespace godot;

#include "character/player/state/player_state.h"

class PlayerWeaponNoneState : public PlayerState {
	GDCLASS(PlayerWeaponNoneState, PlayerState)

public:
	virtual void enter() override {}
	virtual StringName on_process(double delta) override { return StringName(); }
	virtual void on_physics_process(double delta) override {}
	virtual void exit() override {}

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_WEAPON_NONE_STATE
