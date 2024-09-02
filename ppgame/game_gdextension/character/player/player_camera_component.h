#ifndef PLAYER_CAMERA_COMPONENT_H
#define PLAYER_CAMERA_COMPONENT_H

#include <godot_cpp/classes/camera2d.hpp>
#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

#include "framework/component.h"

//! 角色摄像机组件
class PlayerCameraComponent : public Component {
	GDCLASS(PlayerCameraComponent, Component)

public:
	//! 获取摄像机
	Camera2D* get_camera();

public:
	PlayerCameraComponent() {}

	// ------------------------------------------

public:
	virtual void _enter_tree() override;

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_CAMERA_COMPONENT_H
