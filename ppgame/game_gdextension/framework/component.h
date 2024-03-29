#ifndef COMPONENT_H
#define COMPONENT_H

class Component {
public:
	virtual void InitializeComponent() = 0;

	// FIXME abstract class  https://github.com/godotengine/godot-cpp/issues/1425
};

#endif // COMPONENT_H
