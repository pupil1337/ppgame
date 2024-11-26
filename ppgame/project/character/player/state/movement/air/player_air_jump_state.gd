class_name PlayerAirJumpState extends PlayerAirBaseState

var desire_jump: bool


func on_enter() -> void:
	super()
	desire_jump = true


func on_process(p_delta: float) -> Script:
	if desire_jump:
		return null
	
	# to Fall
	if not condition.on_ground && condition.velocity.y > 0.0:
		return PlayerAirFallState
	
	return super(p_delta)


func on_physics_process(p_delta: float) -> void:
	if desire_jump:
		character_movement_component.jump(condition.velocity, character_movement_component.jump_height, character_movement_component.jump_duration)
		desire_jump = false
	else:
		var gravity: float = MathUtils.calculate_jump_gravity(character_movement_component.jump_height, character_movement_component.jump_duration)
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
