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
private:
	void _enter_tree();

public:
	void HostGame();
	void JoinGame();

private:
	void peer_connected(int id);
	void peer_disconnected(int id);
	void connected_to_server();
	void connection_failed();
	void server_disconnected();

	Ref<ENetMultiplayerPeer> peer;
};

#endif // MULTIPLAYERSYSTEM_H
