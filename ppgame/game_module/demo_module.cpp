#include "demo_module.h"

#include "core/config/engine.h"
#include "core/string/print_string.h"
#include "scene/main/node.h"

void DemoModule::_notification(int p_notification) {
	if (p_notification == NOTIFICATION_READY) {
		print_line("DemoModule: NOTIFICATION_READY editor/game");

		set_process(true);
	}
	if (p_notification == NOTIFICATION_PROCESS) {
		if (!Engine::get_singleton()->is_editor_hint()) {
			print_line("DemoModule: NOTIFICATION_PROCESS game");
		}
	}
}
