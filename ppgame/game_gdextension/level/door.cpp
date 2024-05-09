#include "door.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/core/property_info.hpp>
#include <godot_cpp/variant/callable_method_pointer.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/variant.hpp>

#include "level/level.h"

void Door::_enter_tree() {
	parent_type::_enter_tree();

	if (!Engine::get_singleton()->is_editor_hint()) {
		if (Level* level = Object::cast_to<Level>(get_parent())) {
			level->doors.push_back(this);
		}

		connect("body_entered", callable_mp(this, &self_type::_body_entered));
		connect("body_exited", callable_mp(this, &self_type::_body_exited));
	}
}

void Door::_body_entered(Node2D* p_body) {
	UtilityFunctions::print("door::_body_entered: ", p_body->get_name());
}

void Door::_body_exited(Node2D* p_body) {
	UtilityFunctions::print("door::_body_exited: ", p_body->get_name());
}

String Door::get_link_level_path() {
	return link_level_path;
}

String Door::get_link_level_player_start_name() {
	return link_level_player_start_name;
}

// ----------------------------------------------------------------------------

void Door::set_link_level_path(const String& p_link_level_path) {
	link_level_path = p_link_level_path;

	update_configuration_warnings();
}

void Door::set_link_level_player_start_name(const String& p_link_level_player_start_name) {
	link_level_player_start_name = p_link_level_player_start_name;

	update_configuration_warnings();
}

PackedStringArray Door::_get_configuration_warnings() const {
	PackedStringArray warnings = parent_type::_get_configuration_warnings();
	if (get_parent()->is_class(Level::get_class_static())) {
		if (link_level_path.is_empty()) {
			warnings.push_back("Not set link_level_path");
		} else if (!FileAccess::file_exists(link_level_path)) {
			warnings.push_back("file: " + link_level_path + " is not exist");
		}
		if (link_level_player_start_name.is_empty()) {
			warnings.push_back("Not set link_level_player_start_name");
		}
	}

	return warnings;
}

void Door::_bind_methods() {
	// link_level_path
	ClassDB::bind_method(D_METHOD(_STR(set_link_level_path), _STR(link_level_path)), &self_type::set_link_level_path);
	ClassDB::bind_method(D_METHOD(_STR(get_link_level_path)), &self_type::get_link_level_path);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, _STR(link_level_path)), _STR(set_link_level_path), _STR(get_link_level_path));

	// link_level_player_start_name
	ClassDB::bind_method(D_METHOD(_STR(set_link_level_player_start_name), _STR(link_level_player_start_name)), &self_type::set_link_level_player_start_name);
	ClassDB::bind_method(D_METHOD(_STR(get_link_level_player_start_name)), &self_type::get_link_level_player_start_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, _STR(link_level_player_start_name)), _STR(set_link_level_player_start_name), _STR(get_link_level_player_start_name));
}
