class_name PlayerGroundRunState extends PlayerGroundBaseState


func on_process(p_delta: float) -> Script:
	# to Idle
	if condition.on_ground and condition.input_sign_x == 0 and condition.velocity.x == 0.0:
		return PlayerGroundIdleState
	
	return super(p_delta)


func on_physics_process(p_delta: float) -> void:
	character_movement_component.input_move(
			p_delta,
			condition.velocity,
			condition.input_sign_x,
			character_movement_component.walk_acceleration,
			character_movement_component.walk_deceleration,
			character_movement_component.walk_turn_speed,
			character_movement_component.walk_max_speed,
			0.0
	)
