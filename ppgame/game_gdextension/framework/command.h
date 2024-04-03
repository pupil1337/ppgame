#ifndef COMMAND_H
#define COMMAND_H

namespace godot {
class Node;
}
using namespace godot;

class Command {
public:
	virtual void execute(Node* p_node) = 0;
};

#endif // COMMAND_H
