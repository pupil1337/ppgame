#include "register_types.h"

#include <core/object/class_db.h>

void initialize_game_module_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
            return;
    }
	// ClassDB::register_class<MyClass>();
}

void uninitialize_game_module_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
            return;
    }
}
