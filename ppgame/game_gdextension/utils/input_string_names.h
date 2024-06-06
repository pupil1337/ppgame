#ifndef INPUT_STRING_NAMES_H
#define INPUT_STRING_NAMES_H

#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/memory.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/string_name.hpp>
using namespace godot;

class InputStringNames {
	friend void initialize_game_gdextension_types(ModuleInitializationLevel p_level);
	friend void uninitialize_game_gdextension_types(ModuleInitializationLevel p_level);

	static InputStringNames* singleton;

	static void create() { singleton = memnew(InputStringNames); }
	static void free() {
		memdelete(singleton);
		singleton = nullptr;
	}

	InputStringNames();

public:
	_FORCE_INLINE_ static InputStringNames* get_singleton() { return singleton; }

	StringName Left;
	StringName Right;
	StringName Up;
	StringName Down;
	StringName Jump;
	StringName Attack;
};

#define InputStringName(m_name) InputStringNames::get_singleton()->m_name

#endif // INPUT_STRING_NAMES_H
