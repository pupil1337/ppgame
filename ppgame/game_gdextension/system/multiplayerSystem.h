#ifndef MULTIPLAYERSYSTEM_H
#define MULTIPLAYERSYSTEM_H

using namespace godot;

class MultiplayerSystem : public Node {
	GDCLASS(MultiplayerSystem, Node);

	static MultiplayerSystem* singleton;

public:
	MultiplayerSystem();
	~MultiplayerSystem();
	static MultiplayerSystem* get_singleton();

protected:
	static void _bind_methods() {}

	// ------------------------------------------

public:
	virtual void _enter_tree() override;

public:
	void hostGame();
	void joinGame();

private:
	Ref<ENetMultiplayerPeer> peer;
	Vector<int32_t> player_uids;
};

#endif // MULTIPLAYERSYSTEM_H
