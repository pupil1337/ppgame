#ifndef PLAYER_CAMERA_COMPONENT_H
#define PLAYER_CAMERA_COMPONENT_H

#include <godot_cpp/classes/camera2d.hpp>
#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

#include "framework/component.h"

class PlayerCameraComponent : public Component {
	GDCLASS(PlayerCameraComponent, Component)
	typedef Component super;

private:
	Camera2D* camera = nullptr;

	// ------------------------------------------

private:
	void set_camera(Camera2D* p_camera);
	Camera2D* get_camera();

protected:
	static void _bind_methods();
};

#endif // PLAYER_CAMERA_COMPONENT_H
