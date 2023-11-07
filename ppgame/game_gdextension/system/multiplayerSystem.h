#ifndef MULTIPLAYERSYSTEM_H
#define MULTIPLAYERSYSTEM_H

using namespace godot;

class MultiplayerSystem : public Node {
	GDCLASS(MultiplayerSystem, Node);

protected:
	static void _bind_methods() {}

	static MultiplayerSystem* singleton;

public:
	MultiplayerSystem();
	~MultiplayerSystem();
	static MultiplayerSystem* get_singleton();

public:
	virtual void _enter_tree() override;

	//~Begin This Class
public:
	void hostGame();
	void joinGame();

	Ref<ENetMultiplayerPeer> peer;
	Vector<int32_t> player_uids;
};

#endif // MULTIPLAYERSYSTEM_H
