#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/ref.hpp>
using namespace godot;

namespace godot {
class AnimatedSprite2D;
}
class PlayerMovementComponent;
class PlayerFiniteStateMachineComponent;

class Player : public CharacterBody2D {
	GDCLASS(Player, CharacterBody2D)

public:
	AnimatedSprite2D* animated_sprite2d = nullptr;
	PlayerMovementComponent* player_movement_component = nullptr;
	PlayerFiniteStateMachineComponent* player_finite_state_machine_component = nullptr;

	virtual void _ready() override;
	virtual void _input(const Ref<InputEvent>& event) override;
	// virtual void _shortcut_input(const Ref<InputEvent>& event) override;
	// virtual void _unhandled_input(const Ref<InputEvent>& event) override;
	// virtual void _unhandled_key_input(const Ref<InputEvent>& event) override;

protected:
	static void _bind_methods();
};

#endif // PLAYER_H
