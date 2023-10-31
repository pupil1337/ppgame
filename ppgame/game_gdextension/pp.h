#ifndef PP_H
#define PP_H

#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

// TODO 头文件
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>

#define PP_Str(x) #x

/**
 * @description: 成员变量声明为PROPERTY
 * @param m_class: 类型
 * @param m_name: 名称
 * @param m_value: 默认值
*/
#define PP_PROPERTY(m_class, m_name, m_value)	\
	m_class m_name = m_value;					\
	void set_##m_name(m_class p_##m_name) {		\
		m_name = p_##m_name;					\
	}											\
	m_class get_##m_name() const {				\
		return m_name;							\
	}											\

/**
 * @description: Editor绑定成员变量PROPERTY
 * @param m_type: Variant变量类型
 * @param m_name: 成员变量
 * @param __VA_ARGS__: PropertyHint p_hint = PROPERTY_HINT_NONE, const String &p_hint_string = "", uint32_t p_usage = 6U, const StringName &p_class_name = class StringName()
*/
#define PP_ADD_PROPERTY(m_type, m_name, ...)																\
	ClassDB::bind_method(D_METHOD(PP_Str(set_##m_name), #m_name), &self_type::set_##m_name);				\
	ClassDB::bind_method(D_METHOD(PP_Str(get_##m_name)), &self_type::get_##m_name);							\
	ADD_PROPERTY(PropertyInfo(m_type, #m_name, __VA_ARGS__), PP_Str(set_##m_name), PP_Str(get_##m_name));	\

#define PP_CONTINUE_IF_GAME\
	if (Engine::get_singleton()->is_editor_hint()) {	\
		return;											\
	}													\

#endif // PP_H
