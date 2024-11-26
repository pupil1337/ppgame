#ifndef DEMO_MODULE_H
#define DEMO_MODULE_H

#include "core/object/object.h"
#include "scene/2d/node_2d.h"

class DemoModule : public Node2D {
	GDCLASS(DemoModule, Node2D)

protected:
	void _notification(int p_notification);
};

#endif // DEMO_MODULE_H
