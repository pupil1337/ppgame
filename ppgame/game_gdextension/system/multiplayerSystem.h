#ifndef MULTIPLAYERSYSTEM_H
#define MULTIPLAYERSYSTEM_H

using namespace godot;

class MultiplayerSystem : public Node {
	GDCLASS(MultiplayerSystem, Node);

	static MultiplayerSystem* singleton;

public:
	MultiplayerSystem();
	~MultiplayerSystem();

protected:
	static void _bind_methods() {}

	// ------------------------------------------

public:
	static void hostGame();
	static void joinGame();

	static void connect(const StringName& signal, const Callable& callable, uint32_t flags = 0U);
	static void disconnect(const StringName& signal, const Callable& callable);

	static int32_t get_unique_id();
	static bool is_server();

private:
	static Ref<MultiplayerAPI> _get_multiplayer();
};

#endif // MULTIPLAYERSYSTEM_H
