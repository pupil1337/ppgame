#ifndef PP_H
#define PP_H

// ----------------------------------------------------------------------------
// godot-cpp
// ----------------------------------------------------------------------------

// gdextension
#include <gdextension_interface.h>

// gen
	// - classes
#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/e_net_connection.hpp>
#include <godot_cpp/classes/e_net_multiplayer_peer.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/multiplayer_api.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>
	// - core
	// - variant
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

// include
	// - classes
#include <godot_cpp/classes/ref.hpp>
	// - core
#include <godot_cpp/core/class_db.hpp>
	// - templates
#include <godot_cpp/templates/hash_map.hpp>
	// - variant


/**
 * 成员变量声明为PROPERTY
 * @param m_class 类型
 * @param m_name 名称
*/
#define PP_PROPERTY(m_class, m_name)			\
	void set_##m_name(m_class p_##m_name) {		\
		m_name = p_##m_name;					\
	}											\
												\
	m_class get_##m_name() const {				\
		return m_name;							\
	}											\
	m_class m_name

/**
 * Editor绑定成员变量PROPERTY
 * @param m_type: Variant变量类型
 * @param m_name: 成员变量
 * @param __VA_ARGS__: PropertyHint p_hint = PROPERTY_HINT_NONE, const String &p_hint_string = "", uint32_t p_usage = 6U, const StringName &p_class_name = class StringName()
*/
#define PP_ADD_PROPERTY(m_type, m_name, ...)															\
	ClassDB::bind_method(D_METHOD(_STR(set_##m_name), #m_name), &self_type::set_##m_name);				\
	ClassDB::bind_method(D_METHOD(_STR(get_##m_name)), &self_type::get_##m_name);						\
	ADD_PROPERTY(PropertyInfo(m_type, #m_name, __VA_ARGS__), _STR(set_##m_name), _STR(get_##m_name))

/**
 * 如果是Game则继续执行，否则return
*/
#define PP_CONTINUE_IF_GAME								\
	if (Engine::get_singleton()->is_editor_hint()) {	\
		return;											\
	}

#endif // PP_H
