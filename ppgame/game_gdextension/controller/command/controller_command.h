#ifndef CONTROLLER_COMMAND_H
#define CONTROLLER_COMMAND_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/defs.hpp>

#include "framework/command.h"

using namespace godot;

class ControllerMotionCommand : public Command {
public:
	void execute(Node* p_node);

	ControllerMotionCommand() = delete;
	ControllerMotionCommand(real_t p_x, real_t p_y) :
			x(p_x), y(p_y) {}

private:
	real_t x = 0.0;
	real_t y = 0.0;
};

class ControllerJumpCommand : public Command {
public:
	virtual void execute(Node* p_node) override;
};

#endif // CONTROLLER_COMMAND_H
