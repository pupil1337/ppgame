class_name Character extends CharacterBody2D

@onready var sprite: Sprite2D = $Sprite2D
@onready var collision_shape: CollisionShape2D = $CollisionShape2D

func face_to_input(p_input_sign_x: int) -> void:
	sprite.flip_h = p_input_sign_x < 0
