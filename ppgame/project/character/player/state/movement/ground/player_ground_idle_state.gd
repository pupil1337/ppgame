class_name PlayerGroundIdleState extends PlayerGroundBaseState


func on_process(p_delta: float) -> Script:
	# to Run
	if condition.on_ground and condition.input_sign_x != 0:
		return PlayerGroundRunState
	
	return super(p_delta)
