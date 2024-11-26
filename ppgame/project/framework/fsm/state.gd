class_name State extends Node

@export var is_default_state: bool


func _notification(what: int) -> void:
	if what == NOTIFICATION_PARENTED:
		var fsm: FiniteStateMachineComponent = NodeUtils.get_parent_node_lowest_by_script(self, FiniteStateMachineComponent)
		fsm.add_state(self)


func on_enter() -> void:
	pass


@warning_ignore("unused_parameter")
func on_process(p_delta: float) -> Script:
	return null


@warning_ignore("unused_parameter")
func on_physics_process(p_delta: float) -> void:
	pass


func on_exit() -> void:
	pass
