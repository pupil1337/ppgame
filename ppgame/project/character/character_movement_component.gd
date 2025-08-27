class_name CharacterMovementComponent extends Component

@export_group("Walk")
@export var walk_acceleration: int = 600
@export var walk_deceleration: int = 5000
@export var walk_turn_speed: int = 1200
@export var walk_max_speed: int = 400

@export_group("Jump")
@export var jump_height: int = 96
@export var jump_duration: float = 0.4

@export_group("Fall")
@export var fall_gravity_multiplier: float = 2.0

@onready var character: Character = $".."

## 移动输入[br]
## [param p_delta]: delta time[br]
## [param p_curr_velocity]: 当前速度[br]
## [param p_input_sigin_x]: 输入x轴方向[br]
## [param p_acceleration_x]: x轴输入时 加速度[br]
## [param p_deceleration_x]: x轴不输入时 减速度[br]
## [param p_turn_speed_x]: x轴与速度方向相反时候 转体速度[br]
## [param p_max_speed_x]: 最大x轴速度[br]
## [param p_gravity]: 重力大小[br]
func input_move(p_delta: float, p_curr_velocity: Vector2, p_input_sigin_x: int, p_acceleration_x: float, p_deceleration_x: float, p_turn_speed_x: float, p_max_speed_x: float, p_gravity: float) -> void:
	# x
	var speed_change_x: float
	if p_input_sigin_x != 0:
		if signi(p_input_sigin_x) != signf(p_curr_velocity.x):
			speed_change_x = p_turn_speed_x * p_delta
		else:
			speed_change_x = p_acceleration_x * p_delta
	else:
		speed_change_x = p_deceleration_x * p_delta
	var new_velocity_x: float = move_toward(p_curr_velocity.x, p_input_sigin_x * p_max_speed_x, speed_change_x)
	
	# y
	var new_velocity_y: float = p_curr_velocity.y + p_gravity * p_delta
	
	_move_and_slide(Vector2(new_velocity_x, new_velocity_y))


## 向上跳跃[br]
## [param p_curr_velocity]: 当前速度[br]
## [param p_jump_height]: 跳跃高度[br]
## [param p_jump_duration]: 跳跃时间[br]
func jump(p_curr_velocity: Vector2, p_jump_height: float, p_jump_duration: float) -> void:
	var new_velocity_y: float = MathUtils.calculate_jump_speed_y(p_jump_height, p_jump_duration)
	_move_and_slide(Vector2(p_curr_velocity.x, new_velocity_y))


## 向下跳跃[br]
func jump_down(p_curr_velocity: Vector2) -> void:
	if character.collision_mask & Types.PhysicsLayer.ONEWAY:
		var shape: RectangleShape2D = character.collision_shape.shape
		var motion: Vector2 = Vector2(0.0, character.floor_snap_length*2.0)
		var results: Array[Types.ShapeResult]
		DrawDebugUtils.draw_debug_rect(Rect2(character.global_position - shape.size/2.0 + motion, shape.size), 3.0, Color(1.0, 1.0, 1.0, 0.4))
		if PhysicsUtils.shape_cast_rectangle(
				character,
				character.global_transform,
				shape.size / 2.0,
				motion,
				results,
				character.collision_mask,
				[character.get_rid()],
				false,
				true,
				0.0,
				32
		):
			for result: Types.ShapeResult in results:
				var collider_layer: int = PhysicsServer2D.body_get_collision_layer(result.rid)
				if collider_layer & ~Types.PhysicsLayer.ONEWAY:
					return
			character.collision_mask &= ~Types.PhysicsLayer.ONEWAY
			character.global_translate(motion)
			_move_and_slide(p_curr_velocity)
			character.collision_mask |= Types.PhysicsLayer.ONEWAY


#region
func _move_and_slide(p_new_velocity: Vector2) -> void:
	assert(Engine.is_in_physics_frame(), "建议在物理帧中操作物理对象位置")
	character.velocity = p_new_velocity
	@warning_ignore("return_value_discarded")
	character.move_and_slide()
#endregion
