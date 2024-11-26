#include "register_types.h"

#include "core/object/class_db.h"
#include "modules/register_module_types.h"

#include "demo_module.h"

void initialize_game_module_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	GDREGISTER_CLASS(DemoModule)
}

void uninitialize_game_module_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}
