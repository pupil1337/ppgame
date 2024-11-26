class_name Level extends Node

@onready var camera_limit_LT: Marker2D = $CameraLimitLT
@onready var camera_limit_RB: Marker2D = $CameraLimitRB


## 获取相机限制[br]
## 返回 { SIDE_LEFT: float, SIDE_RIGHT: float, SIDE_TOP: float, SIDE_BOTTOM: float }[br]
func get_camera_limit() -> Dictionary:
	var origin_LT: Vector2 = camera_limit_LT.get_transform().get_origin()
	var origin_RB: Vector2 = camera_limit_RB.get_transform().get_origin()
	return {
		SIDE_LEFT: origin_LT.x,
		SIDE_RIGHT: origin_RB.x,
		SIDE_TOP: origin_LT.y,
		SIDE_BOTTOM: origin_RB.y
	}
	
