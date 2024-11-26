class_name PlayerAirBaseState extends PlayerState


@warning_ignore("unused_parameter")
func on_process(p_delta: float) -> Script:
	# ground state
	# to Idle
	if condition.on_ground and condition.input_sign_x == 0 and condition.velocity.x == 0.0:
		return PlayerGroundIdleState
	# to Run
	if condition.on_ground and (condition.input_sign_x != 0 or condition.velocity.x != 0.0):
		return PlayerGroundRunState
	
	return null
