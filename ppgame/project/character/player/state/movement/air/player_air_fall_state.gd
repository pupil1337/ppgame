class_name PlayerAirFallState extends PlayerAirBaseState


func on_physics_process(p_delta: float) -> void:
	var gravity: float = MathUtils.calculate_fall_gravity(character_movement_component.jump_height, character_movement_component.jump_duration, character_movement_component.fall_gravity_multiplier)
	character_movement_component.input_move(
			p_delta,
			condition.velocity,
			condition.input_sign_x,
			character_movement_component.walk_acceleration,
			character_movement_component.walk_deceleration,
			character_movement_component.walk_turn_speed,
			character_movement_component.walk_max_speed,
			gravity
	)
