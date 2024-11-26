class_name PlayerAirJumpDownState extends PlayerAirBaseState

var desire_jump_down: bool


func on_enter() -> void:
	desire_jump_down = true


func on_process(p_delta: float) -> Script:
	if desire_jump_down:
		return null
	
	# to Jump
	if condition.on_ground:
		return PlayerAirJumpState
	
	# to Fall
	if not condition.on_ground:
		return PlayerAirFallState
	
	return super(p_delta)


@warning_ignore("unused_parameter")
func on_physics_process(p_delta: float) -> void:
	if desire_jump_down:
		character_movement_component.jump_down(condition.velocity)
		desire_jump_down = false
