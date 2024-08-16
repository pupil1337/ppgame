#ifndef PP_TYPES_H
#define PP_TYPES_H

#include <cstdint>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/object_id.hpp>
#include <godot_cpp/variant/rid.hpp>
#include <godot_cpp/variant/vector2.hpp>
using namespace godot;

//! 方向
enum class Direction {
	Right,
	Left,
	Up,
	Down,
	RightUp,
	RightDown,
	LeftUp,
	LeftDown,
	None
};

// clang-format off

//! 碰撞层
enum class CollisionLayer : uint32_t {
	World   = 0b00000000000000000000000000000001,
	Player  = 0b00000000000000000000000000000010,
	OneWay  = 0b00000000000000000000000000000100,

	None    = 0b00000000000000000000000000000000,
	ALL     = 0b11111111111111111111111111111111
};

// clang-format on

//! 射线检测结果
struct RayResult {
	Vector2 position;
	Vector2 normal;
	RID rid;
	ObjectID collider_id;
	Object* collider;
	int shape;
};

//! 形状检测结果
struct ShapeResult {
	RID rid;
	ObjectID collider_id;
	Object* collider = nullptr;
	int shape = 0;
};

#endif // PP_TYPES_H
