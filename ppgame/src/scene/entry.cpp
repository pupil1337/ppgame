#include "entry.h"

#include <scene/main/window.h>
#include "system/multiplayerSystem.h"

void Entry::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_ENTER_TREE: {
			_enter_tree();
		} break;
	}
}

void Entry::_enter_tree() {
	initialize_system();
	open_menu_main();
}

void Entry::initialize_system() {
	MultiplayerSystem* multiplayerSystem = memnew(MultiplayerSystem);
	get_tree()->get_root()->add_child(multiplayerSystem);
	print_line(multiplayerSystem);
}

void Entry::open_menu_main() {

}
