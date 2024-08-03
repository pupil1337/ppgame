#include "door.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/memory.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/core/property_info.hpp>
#include <godot_cpp/variant/callable_method_pointer.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/variant.hpp>

#include "character/player/player.h"
#include "level/level.h"
#include "world/world.h"

void Door::_notification(int p_what) {
	if (!Engine::get_singleton()->is_editor_hint()) {
		if (p_what == NOTIFICATION_POSTINITIALIZE) {
			connect("body_entered", callable_mp(this, &self_type::_body_entered));
			connect("body_exited", callable_mp(this, &self_type::_body_exited));
		} else if (p_what == NOTIFICATION_PREDELETE) {
			disconnect("body_entered", callable_mp(this, &self_type::_body_entered));
			disconnect("body_exited", callable_mp(this, &self_type::_body_exited));
		}
	}
}

void Door::_body_entered(Node2D* p_body) {
	UtilityFunctions::print(get_parent()->get_name(), "->", get_name(), " _body_entered:", p_body->get_name());
	if (Player* player = Object::cast_to<Player>(p_body)) {
		call_deferred(_STR(set_monitoring), false);
		if (World* world = World::get_world(this)) {
			world->change_level(link_level_path, link_level_player_start_name);
		}
	}
}

void Door::_body_exited(Node2D* p_body) {
	UtilityFunctions::print(get_parent()->get_name(), "->", get_name(), " _body_exited:", p_body->get_name());
}

// ----------------------------------------------------------------------------

void Door::set_link_level_path(const String& p_link_level_path) {
	link_level_path = p_link_level_path;

	update_configuration_warnings();
}

String Door::get_link_level_path() {
	return link_level_path;
}

void Door::set_link_level_player_start_name(const String& p_link_level_player_start_name) {
	link_level_player_start_name = p_link_level_player_start_name;

	update_configuration_warnings();
}

String Door::get_link_level_player_start_name() {
	return link_level_player_start_name;
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
