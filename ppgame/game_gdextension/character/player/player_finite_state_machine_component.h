#ifndef PLAYER_FINITE_STATE_MACHINE_COMPONENT_H
#define PLAYER_FINITE_STATE_MACHINE_COMPONENT_H

#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/core/defs.hpp>
using namespace godot;

#include "character/player/state/player_state_condition.h"
#include "fsm/finite_state_machine_component.h"

class Player;
class PlayerInputComponent;

class PlayerFiniteStateMachineComponent : public FiniteStateMachineComponent {
	GDCLASS(PlayerFiniteStateMachineComponent, FiniteStateMachineComponent)

public:
	virtual void on_process(double p_delta) override;
	virtual void on_physics_process(double p_delta) override;

private:
	void _update_logic_condition();
	void _update_physics_condition();

private:
	Player* player = nullptr;
	PlayerInputComponent* player_input_component = nullptr;

	PlayerStateCondition condition;

	// ------------------------------------------

public:
	virtual void _ready() override;

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_FINITE_STATE_MACHINE_COMPONENT_H
