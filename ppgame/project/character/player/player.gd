class_name Player extends Character

@onready var melee_attack_collision_shape: CollisionShape2D = $MeleeAttackArea2D/MeleeAttackCollisionShape2D


func _ready() -> void:
	DrawDebugUtils.draw_debug_line(Vector2(1920.0, 1080.0), Vector2(0.0, 0.0), 3)

func face_to_input(p_input_sign_x: int) -> void:
	super(p_input_sign_x)
	if p_input_sign_x != 0:
		melee_attack_collision_shape.apply_scale(Vector2(p_input_sign_x, 1.0))
