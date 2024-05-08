#ifndef DOOR_H
#define DOOR_H

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>
#include <godot_cpp/variant/string.hpp>
using namespace godot;

class Door : public Area2D {
	GDCLASS(Door, Area2D)

private:
	void _body_entered(Node2D* p_body);
	void _body_exited(Node2D* p_body);

private:
	bool auto_door = true;

	String link_level_path;
	String link_level_player_start_name;

	// ------------------------------------------

public:
	String get_link_level_path();
	String get_link_level_player_start_name();

private:
	void set_link_level_path(const String& p_link_level_path);
	void set_link_level_player_start_name(const String& p_link_level_player_start_name);

public:
	virtual void _enter_tree() override;
	virtual PackedStringArray _get_configuration_warnings() const override;

protected:
	static void _bind_methods();
};

#endif // DOOR_H
