class_name PlayerCameraComponent extends Component

@onready var camera: Camera2D = $Camera2D


func _enter_tree() -> void:
	do_camera_limit.call_deferred()


func do_camera_limit() -> void:
	var level: Level = NodeUtils.get_parent_node_lowest_by_script(self, Level)
	var camera_limit: Dictionary = level.get_camera_limit()
	camera.limit_left = camera_limit[SIDE_LEFT]
	camera.limit_right = camera_limit[SIDE_RIGHT]
	camera.limit_top = camera_limit[SIDE_TOP]
	camera.limit_bottom = camera_limit[SIDE_BOTTOM]
