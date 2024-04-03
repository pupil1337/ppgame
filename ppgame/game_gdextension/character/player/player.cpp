#include "player.h"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/core/defs.hpp"
#include "godot_cpp/core/object.hpp"
#include "godot_cpp/core/property_info.hpp"
#include "godot_cpp/variant/variant.hpp"

#include <cstdint>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/ref.hpp>

void Player::_ready() {
	initialize_components();
}

void Player::set_id(uint32_t p_id) {
	id = p_id + 1;
}

uint32_t Player::get_id() const {
	return id;
}

void Player::_bind_methods() {
	// id
	ClassDB::bind_method(D_METHOD(_STR(set_id), _STR(id)), &self_type::set_id);
	ClassDB::bind_method(D_METHOD(_STR(get_id)), &self_type::get_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, _STR(id)), _STR(set_id), _STR(get_id));
}
