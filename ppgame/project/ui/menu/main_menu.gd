extends Control

# Menu List
@onready var menu_list_control = $MenuListControl as Control
@onready var start_button = $MenuListControl/VBoxContainer/StartButton as Button
@onready var setting_button = $MenuListControl/VBoxContainer/SettingButton as Button
@onready var exit_button = $MenuListControl/VBoxContainer/ExitButton as Button
# Press Any Key Start
@onready var pressed_any_key_start_label = $PressedAnyKeyStartLabel as Label

func _input(event: InputEvent) -> void:
	if pressed_any_key_start_label.is_visible_in_tree():
		accept_event()
		if event.is_action_type() && (!event is InputEventMouseButton || (event as InputEventMouseButton).button_index != MOUSE_BUTTON_WHEEL_UP && (event as InputEventMouseButton).button_index != MOUSE_BUTTON_WHEEL_DOWN) && !event is InputEventJoypadMotion:
			_on_any_key_pressed()

# 点击任意键开始
func _on_any_key_pressed() -> void:
	pressed_any_key_start_label.visible = false
	menu_list_control.visible = true

# 开始游戏按钮
func _on_start_button_pressed() -> void:
	var world = load("res://world.tscn").instantiate()
	get_tree().root.add_child(world)
	hide()

# 设置按钮
func _on_setting_button_pressed() -> void:
	pass

# 退出按钮
func _on_exit_button_pressed() -> void:
	get_tree().quit()
	pass
