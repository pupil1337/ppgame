class_name MathUtils extends Object

## 向上跳跃-计算速度y[br]
## [param p_jump_height]: 向上跳跃高度[br]
## [param p_jump_duration]: 向上跳跃时间[br]
static func calculate_jump_speed_y(p_jump_height: float, p_jump_duration: float) -> float:
	return (2.0 * -p_jump_height) / p_jump_duration


## 向上跳跃-计算重力[br]
## [param p_jump_height]: 向上跳跃高度[br]
## [param p_jump_duration]: 向上跳跃时间[br]
static func calculate_jump_gravity(p_jump_height: float, p_jump_duration: float) -> float:
	return (-2.0 * -p_jump_height) / (p_jump_duration * p_jump_duration)


## 下坠-计算重力[br]
## [param p_jump_height]: 向上跳跃高度[br]
## [param p_jump_duration]: 向上跳跃时间[br]
## [param p_fall_gravity_multiplier]: 下坠时相对与向上跳跃的重力乘数[br]
static func calculate_fall_gravity(p_jump_height: float, p_jump_duration: float, p_fall_gravity_multiplier: float) -> float:
	return calculate_jump_gravity(p_jump_height, p_jump_duration) * p_fall_gravity_multiplier


## 获取目标坐标相对于自己方向[br]
## [param p_vector]: 目标坐标[br]
static func get_direction(p_vector: Vector2) -> Types.Direction:
	if p_vector.is_zero_approx():
		return Types.Direction.NONE
	
	var PI1_8: float = PI * 1.0 / 8.0
	var PI3_8: float = PI * 3.0 / 8.0
	var PI5_8: float = PI * 5.0 / 8.0
	var PI7_8: float = PI * 7.0 / 8.0
	
	var radian: float = p_vector.angle()
	if radian > -PI1_8 and radian <= PI1_8: return Types.Direction.RIGHT
	elif radian <= -PI7_8 or radian > PI7_8: return Types.Direction.LEFT
	elif radian > -PI5_8 and radian <= -PI3_8: return Types.Direction.UP
	elif radian <= PI5_8 and radian > PI3_8: return Types.Direction.DOWN
	elif radian > -PI3_8 and radian <= -PI1_8: return Types.Direction.RIGHT_UP
	elif radian <= PI3_8 and radian > PI1_8: return Types.Direction.RIGHT_DOWN
	elif radian > -PI7_8 and radian <= -PI5_8: return Types.Direction.LEFT_UP
	elif radian <= PI7_8 and radian > PI5_8: return Types.Direction.LEFT_DOWN
	assert(false, "没计算出方向?")
	
	return Types.Direction.NONE


## 获取方向-正负(通过方向)[br]
## [param p_dir]: 方向[br]
static func get_direction_sign_by_direction(p_dir: Types.Direction) -> Vector2i:
	match p_dir:
		Types.Direction.NONE:
			return Vector2(0, 0)
		Types.Direction.LEFT:
			return Vector2(-1, 0)
		Types.Direction.RIGHT:
			return Vector2(1, 0)
		Types.Direction.UP:
			return Vector2(0, -1)
		Types.Direction.DOWN:
			return Vector2(0, 1)
		Types.Direction.LEFT_UP:
			return Vector2(-1, -1)
		Types.Direction.LEFT_DOWN:
			return Vector2(-1, 1)
		Types.Direction.RIGHT_UP:
			return Vector2(1, -1)
		Types.Direction.RIGHT_DOWN:
			return Vector2(1, 1)
	
	return Vector2(0, 0)


## 获取方向-正负(通过向量)[br]
## [param p_vector]: 向量[br]
static func get_direction_sign_by_vector(p_vector: Vector2) -> Vector2i:
	return get_direction_sign_by_direction(get_direction(p_vector))


## 圆内随机找一点[br]
## [param p_position]: 位置[br]
## [param p_radius]: 半径[br]
static func random_point_in_circle(p_position: Vector2, p_radius: float) -> Vector2:
	var radian: float = randf_range(0.0, 2.0 * PI)
	var radius: float = randf_range(0.0, p_radius)
	return Vector2(p_position.x + radius * cos(radian), p_position.y - radius * sin(radian))
