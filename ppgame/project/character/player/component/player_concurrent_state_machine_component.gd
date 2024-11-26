class_name PlayerConcurrentStateMachineComponent extends ConcurrentStateMachineComponent

@onready var player: Player = $".."
@onready var player_input_component: PlayerInputComponent = $"../PlayerInputComponent"


func _init() -> void:
	super(PlayerStateCondition)


func update_logic_condition() -> void:
	(condition as PlayerStateCondition).input_sign_x = player_input_component.motion_sign.x
	(condition as PlayerStateCondition).input_sign_y = player_input_component.motion_sign.y
	(condition as PlayerStateCondition).just_pressed_jump = player_input_component.just_pressed_jump
	(condition as PlayerStateCondition).just_pressed_attack = player_input_component.just_pressed_attack


func update_physics_condition() -> void:
	(condition as PlayerStateCondition).on_ground = player.is_on_floor()
	(condition as PlayerStateCondition).velocity = player.velocity
