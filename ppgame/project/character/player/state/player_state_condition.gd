class_name PlayerStateCondition extends StateCondition

# ---------------------------
# logic
# ---------------------------
# input
var input_sign_x: int
var input_sign_y: int
var just_pressed_jump: bool
var just_pressed_attack: bool


# ---------------------------
# physics
# ---------------------------
# state
var on_ground: bool
var velocity: Vector2
