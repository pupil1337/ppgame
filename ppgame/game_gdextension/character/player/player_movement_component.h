#ifndef PLAYER_MOVEMENT_COMPONENT_H
#define PLAYER_MOVEMENT_COMPONENT_H

#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

#include "framework/component.h"

class PlayerInputComponent;

class PlayerMovementComponent : public Component {
	GDCLASS(PlayerMovementComponent, Component)

public:
	virtual void _ready() override;
	virtual void _process(double delta) override;
	virtual void _physics_process(double delta) override;

private:
	PlayerInputComponent* player_input_component = nullptr;

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_MOVEMENT_COMPONENT_H
