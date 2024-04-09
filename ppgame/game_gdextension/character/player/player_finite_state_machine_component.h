#ifndef PLAYER_FINITE_STATE_MACHINE_COMPONENT_H
#define PLAYER_FINITE_STATE_MACHINE_COMPONENT_H

#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/core/defs.hpp>
using namespace godot;

#include "fsm/finite_state_machine_component.h"

class Player;
struct PlayerStateCondition;

class PlayerFiniteStateMachineComponent : public FiniteStateMachineComponent {
	GDCLASS(PlayerFiniteStateMachineComponent, FiniteStateMachineComponent)

public:
	virtual void on_process(double p_delta) override;

public:
	PlayerFiniteStateMachineComponent();
	~PlayerFiniteStateMachineComponent();

private:
	Player* player = nullptr;
	PlayerStateCondition* condition = nullptr;

	// ------------------------------------------

public:
	virtual void _ready() override;

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_FINITE_STATE_MACHINE_COMPONENT_H
