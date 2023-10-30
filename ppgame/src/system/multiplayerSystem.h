#ifndef MULTIPLAYERSYSTEM_H
#define MULTIPLAYERSYSTEM_H

#include <scene/main/node.h>
#include <core/os/thread_safe.h>

class MultiplayerSystem : public Node {
	GDCLASS(MultiplayerSystem, Node);
	_THREAD_SAFE_CLASS_

	static MultiplayerSystem* singleton;

public:
	MultiplayerSystem();
	~MultiplayerSystem();
	static MultiplayerSystem* get_singleton();

//~Begin This Class
private:
	
};

#endif // MULTIPLAYERSYSTEM_H
