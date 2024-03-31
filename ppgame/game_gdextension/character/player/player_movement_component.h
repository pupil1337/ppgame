#ifndef PLAYER_MOVEMENT_COMPONENT_H
#define PLAYER_MOVEMENT_COMPONENT_H

#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

#include "framework/component.h"

class PlayerMovementComponent : public Component {
	GDCLASS(PlayerMovementComponent, Component)

public:
	virtual void initialize_component() override;

	// ------------------------------------------

protected:
	static void _bind_methods();
};

#endif // PLAYER_MOVEMENT_COMPONENT_H
