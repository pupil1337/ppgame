#ifndef ENTRY_H
#define ENTRY_H

#include <scene/main/node.h>

class Entry : public Node {
	GDCLASS(Entry, Node)

protected:
	void _notification(int p_notification);

//~Begin This Class
private:
	void _enter_tree();

	void initialize_system();
	void open_menu_main();
};

#endif // ENTRY_H
