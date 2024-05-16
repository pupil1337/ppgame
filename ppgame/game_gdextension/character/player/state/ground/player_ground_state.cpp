#include "player_ground_state.h"

#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "character/player/player.h"
#include "character/player/state/air/player_air_fall_state.h"
#include "character/player/state/air/player_air_jump_state.h"
#include "character/player/state/player_state_condition.h"
#include "utils/physics_utils.h"
#include "utils/types.h"

StringName PlayerGroundState::on_process(double delta) {
	if (condition) {
		// air state
		// one way down jump
		if (condition->input_sign_y > 0 && condition->just_pressed_jump) {
			RayResult ray_result;
			if (PhysicsUtils::ray_cast(
						player,
						player->get_position(),
						player->get_position() + Vector2(0.0, 33.0), // TODO
						ray_result,
						{ CollisionLayer::World },
						{ player->get_rid() },
						true,
						false,
						true)) {
				UtilityFunctions::print("one way down jump: rid->", ray_result.rid);
				UtilityFunctions::print("one way down jump: collider->", ray_result.collider);
				UtilityFunctions::print("one way down jump: collider->collider_id", ray_result.collider_id);
				UtilityFunctions::print("one way down jump: collider->get_instance_id", ray_result.collider->get_instance_id());
			}
		}
		// jump
		if (condition->just_pressed_jump && condition->can_jump) {
			return PlayerAirJumpState::get_class_static();
		}
		// fall
		if (!condition->on_ground) {
			return PlayerAirFallState::get_class_static();
		}
	}

	return StringName();
}
