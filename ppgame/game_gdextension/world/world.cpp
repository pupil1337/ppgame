#include "world.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/marker2d.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/physics_server2d.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/memory.hpp>
#include <godot_cpp/variant/callable_method_pointer.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/transform2d.hpp>

#include "async_loader/async_loader.h"
#include "character/player/player.h"
#include "character/player/player_finite_state_machine_component.h"
#include "character/player/state/player_fsm_input_types.h"
#include "gm/gm.h"
#include "level/level.h"
#include "utils/debug_draw_utils.h"

static AsyncLoader* async_loader = nullptr;
static GM* gm = nullptr;
static DebugDrawUtils* debug_draw_utils = nullptr;

void World::_notification(int p_what) {
	if (!Engine::get_singleton()->is_editor_hint()) {
		switch (p_what) {
			case NOTIFICATION_POSTINITIALIZE: {
				async_loader = memnew(AsyncLoader);
				gm = memnew(GM);
			} break;
			case NOTIFICATION_SCENE_INSTANTIATED: {
				// 在PackedScene::instantiate()中会调用_add_child_nocheck(), instantiate()结束后会立即调用此notify
				// 所以在此notify中add_child()即可
				debug_draw_utils = memnew(DebugDrawUtils);
				add_child(debug_draw_utils);
			} break;
			case NOTIFICATION_PREDELETE: {
				if (async_loader) {
					memdelete(async_loader);
				}
				if (gm) {
					memdelete(gm);
				}
			} break;
		}
	}
}

void World::_enter_tree() {
	parent_type::_enter_tree();

	if (!Engine::get_singleton()->is_editor_hint()) {
		player = Object::cast_to<Player>(AsyncLoader::get_singleton()->instance("res://character/player/player.tscn"));
		add_child(player);
	}
}

void World::_ready() {
	parent_type::_ready();

	if (!Engine::get_singleton()->is_editor_hint()) {
		remove_child(player);
		change_level("res://level/level_0.tscn", "PlayerStart0");
	}
}

void World::_process(double delta) {
	parent_type::_process(delta);
}

void World::_exit_tree() {
	parent_type::_exit_tree();
}

World* World::get_world(Node* p_inside_node) {
	if (p_inside_node->is_inside_tree()) {
		return p_inside_node->get_tree()->get_root()->get_node<World>("World");
	}

	return nullptr;
}

void World::change_level(const String& p_level, const String& p_player_start) {
	AsyncLoader::get_singleton()->instance(p_level, callable_mp(this, &self_type::_change_level_implement).bind(p_player_start));
}

void World::_change_level_implement(Node* p_node, const String& p_player_start) {
	if (Level* level = Object::cast_to<Level>(p_node)) {
		// 传送前处理 --------------------------------------
		// player状态改变
		if (PlayerFiniteStateMachineComponent* player_fsm_component = player->get_component<PlayerFiniteStateMachineComponent>()) {
			player_fsm_component->on_input(PlayerFSMInput::To_Movement_None_State, 1);
			player_fsm_component->on_input(PlayerFSMInput::To_Weapon_None_State, 1);
		}
		// 删除当前关卡
		if (curr_level) {
			curr_level->remove_child(player);
			curr_level->set_process_mode(Node::PROCESS_MODE_DISABLED);
			remove_child(curr_level);
			curr_level->queue_free();
		}

		// 传送 ------------------------------------------
		// 切换关卡
		curr_level = level;
		add_child(curr_level);

		// player传送
		curr_level->add_child(player);
		Marker2D* player_start = curr_level->get_node<Marker2D>(p_player_start);
		const Transform2D& player_start_x = player_start->get_transform();
		player->set_transform(player_start_x);
		PhysicsServer2D::get_singleton()->body_set_mode(player->get_rid(), PhysicsServer2D::BODY_MODE_STATIC);
		PhysicsServer2D::get_singleton()->body_set_state(player->get_rid(), PhysicsServer2D::BODY_STATE_TRANSFORM, player_start_x);
		PhysicsServer2D::get_singleton()->body_set_mode(player->get_rid(), PhysicsServer2D::BODY_MODE_KINEMATIC);

		// 传送后处理 --------------------------------------
		// player状态改变
		if (PlayerFiniteStateMachineComponent* player_fsm_component = player->get_component<PlayerFiniteStateMachineComponent>()) {
			player_fsm_component->on_input(PlayerFSMInput::To_Movement_None_State, -1);
			player_fsm_component->on_input(PlayerFSMInput::To_Weapon_None_State, -1);
		}
	}
}
