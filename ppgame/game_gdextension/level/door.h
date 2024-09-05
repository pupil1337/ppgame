#ifndef DOOR_H
#define DOOR_H

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>
#include <godot_cpp/variant/string.hpp>
using namespace godot;

//! 关卡传送门
class Door : public Area2D {
	GDCLASS(Door, Area2D)

private:
	//! body_entered信号
	void _body_entered(Node2D* p_body);
	//! body_exited信号
	void _body_exited(Node2D* p_body);

public:
	Door() {}

private:
	String link_level_path; //!< 连接关卡
	String link_level_player_start_name; //!< 连接关卡的玩家生成点

	// ------------------------------------------

private:
	void set_link_level_path(const String& p_link_level_path);
	String get_link_level_path();
	void set_link_level_player_start_name(const String& p_link_level_player_start_name);
	String get_link_level_player_start_name();

public:
	virtual PackedStringArray _get_configuration_warnings() const override;

protected:
	static void _bind_methods();
	void _notification(int p_what);
};

#endif // DOOR_H
