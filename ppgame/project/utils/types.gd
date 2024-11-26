# class_name Types
# autoload
extends Node

## 方向
enum Direction {
	NONE,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	LEFT_UP,
	LEFT_DOWN,
	RIGHT_UP,
	RIGHT_DOWN,
}


## 射线检测结果
class RayResult extends RefCounted:
	var position: Vector2
	var normal: Vector2
	var collider_id: int
	var collider: Object
	var shape: int
	var rid: RID


## 形状检测结果
class ShapeResult extends RefCounted:
	var rid: RID
	var collider_id: int
	var collider: Object
	var shape: int


## 物理层
enum PhysicsLayer {
	WORLD  = 0b00000000000000000000000000000001,
	PLAYER = 0b00000000000000000000000000000010,
	ONEWAY = 0b00000000000000000000000000000100,
}


func _init() -> void:
	assert(_check_physics_layer_enum() or true, "请检查PhysicsLayer枚举名称应该与ProjectSettings中layer_names/2d_physics/layer_*的'名称和值'一致")

#region
# 检查PhysicsLayer枚举定义(只在调试版本或者从编辑器运行项目时调用)
func _check_physics_layer_enum() -> bool:
	# 检查已经定义的枚举是否正确
	var layer_index: int = 1
	for layer: String in PhysicsLayer:
		var setting_layer_name: String = "layer_names/2d_physics/layer_" + str(layer_index)
		var setting_layer: String = ProjectSettings.get_setting(setting_layer_name)
		# 定义了枚举但是枚举名称与项目设置不一致
		if layer.nocasecmp_to(setting_layer) != 0:
			if setting_layer.is_empty():
				push_error("Types.PhysicsLayer."+layer+" 没有在项目设置 "+setting_layer_name+"中定义过")
			else:
				push_error("Types.PhysicsLayer."+layer+" !=项目设置 "+setting_layer_name+":"+setting_layer+"(名称不一致)")
			return false
		# 定义了枚举但是枚举值不对
		if PhysicsLayer[layer] != 1 << layer_index-1:
			push_error("Types.PhysicsLayer."+layer+" value:"+str(PhysicsLayer[layer])+" !=项目设置 "+setting_layer_name+" value:"+str(1 << layer_index-1)+"枚举值定义错误")
			return false
		layer_index += 1
	# 检查是否缺少枚举定义
	while layer_index <= 32:
		var setting_layer_name: String = "layer_names/2d_physics/layer_" + str(layer_index)
		var setting_layer: String = ProjectSettings.get_setting(setting_layer_name)
		if not setting_layer.is_empty():
			push_error("项目设置中已经定义 "+setting_layer_name+":"+setting_layer+ " 但还未在Types.PhysicsLayer中定义")
			return false
		layer_index += 1
	return true
#endregion
