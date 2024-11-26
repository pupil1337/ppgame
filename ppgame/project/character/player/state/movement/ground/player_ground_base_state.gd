class_name PlayerGroundBaseState extends PlayerState


@warning_ignore("unused_parameter")
func on_process(p_delta: float) -> Script:
	# air state
	# jump down
	if condition.on_ground and condition.input_sign_y > 0 and condition.just_pressed_jump:
		return PlayerAirJumpDownState
	# to Jump
	if condition.on_ground and condition.just_pressed_jump:
		return PlayerAirJumpState
	# to Fall
	if not condition.on_ground:
		return PlayerAirFallState
	
	return null
