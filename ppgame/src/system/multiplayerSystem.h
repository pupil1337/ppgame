#ifndef MULTIPLAYERSYSTEM_H
#define MULTIPLAYERSYSTEM_H

#include <scene/main/node.h>
#include <core/os/thread_safe.h>

class ENetMultiplayerPeer;

class MultiplayerSystem : public Node {
	GDCLASS(MultiplayerSystem, Node);
	_THREAD_SAFE_CLASS_

	static MultiplayerSystem* singleton;

public:
	MultiplayerSystem();
	~MultiplayerSystem();
	static MultiplayerSystem* get_singleton();

protected:
	void _notification(int p_notification);

//~Begin This Class
public:
	void HostGame();
	void JoinGame();

private:
	void _enter_tree();

	Ref<ENetMultiplayerPeer> peer;
};

#endif // MULTIPLAYERSYSTEM_H
