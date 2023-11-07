#include "world.h"

#include "scene/player/player.h"

void World::_enter_tree() {
	PP_CONTINUE_IF_GAME

	if (get_multiplayer()->is_server()) {
		get_multiplayer()->connect("peer_connected", callable_mp(this, &World::_add_player));
		get_multiplayer()->connect("peer_disconnected", callable_mp(this, &World::_del_player));
	}
}

void World::_ready() {
	PP_CONTINUE_IF_GAME

	if (get_multiplayer()->is_server()) {
		_add_player(1);
	}
}

void World::_exit_tree() {
	PP_CONTINUE_IF_GAME

	if (get_multiplayer()->is_server()) {
		get_multiplayer()->disconnect("peer_connected", callable_mp(this, &World::_add_player));
		get_multiplayer()->disconnect("peer_disconnected", callable_mp(this, &World::_del_player));
	}
}

void World::_add_player(int32_t uid) {
	Ref<PackedScene> player_packed_scene = ResourceLoader::get_singleton()->load("res://scene/player/player.tscn", "PackedScene");
	ERR_FAIL_NULL_EDMSG(player_packed_scene.ptr(), "player PackedScene path is wrong!");
	Player* player = cast_to<Player>(player_packed_scene.ptr()->instantiate());
	player->uid = uid;
	player->set_name("player" + itos(uid));
	add_child(player, true);
}

void World::_del_player(int32_t uid) {
}
