class_name PlayerInputComponent extends Component

var motion: Vector2
var motion_sign: Vector2i
var just_pressed_jump: bool
var just_pressed_attack: bool


func _process(delta: float) -> void:
	super(delta)
	motion = Input.get_vector("Left", "Right", "Up", "Down")
	motion_sign = MathUtils.get_direction_sign_by_vector(motion)
	just_pressed_jump = Input.is_action_just_pressed("Jump")
	just_pressed_attack = Input.is_action_just_pressed("Attack")
