#include "playerMovementComponent.h"

#include "scene/player/player.h"
#include "system/multiplayerSystem.h"

void PlayerMovementComponent::_bind_methods() {
	// player
	ClassDB::bind_method(D_METHOD(_STR(set_player), _STR(player)), &self_type::set_player);
	ClassDB::bind_method(D_METHOD(_STR(get_player)), &self_type::get_player);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, _STR(player), PROPERTY_HINT_NODE_TYPE, "Player"), _STR(set_player), _STR(get_player));

	ADD_GROUP("Run", "");
	// max_run_speed
	ClassDB::bind_method(D_METHOD(_STR(set_max_run_speed), _STR(max_run_speed)), &self_type::set_max_run_speed);
	ClassDB::bind_method(D_METHOD(_STR(get_max_run_speed)), &self_type::get_max_run_speed);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, _STR(max_run_speed), PROPERTY_HINT_RANGE, "1.0,1920.0,0.1,or_greater,suffix:px"), _STR(set_max_run_speed), _STR(get_max_run_speed));

	ADD_GROUP("Replicate", "");
	// location
	ClassDB::bind_method(D_METHOD(_STR(set_location), _STR(location)), &self_type::set_location);
	ClassDB::bind_method(D_METHOD(_STR(get_location)), &self_type::get_location);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, _STR(location)), _STR(set_location), _STR(get_location));
}

void PlayerMovementComponent::set_player(Player* p_player) {
	player = p_player;
}

void PlayerMovementComponent::set_max_run_speed(float p_max_run_speed) {
	max_run_speed = p_max_run_speed;
}

void PlayerMovementComponent::set_location(const Vector2& p_location) {
	location = p_location;

	PP_CONTINUE_IF_GAME
	ERR_FAIL_NULL(player);
	// TODO
	player->set_position(location);
}

// ----------------------------------------------------------------------------

void PlayerMovementComponent::move() {
	ERR_FAIL_NULL(player);
	player->set_velocity(velocity);
	player->move_and_slide();
	location = player->get_position();
}

void PlayerMovementComponent::apply_gravity(float deltaTime) {
	velocity.y += 9.80f * 2.0f * 16.0f * deltaTime;
}

void PlayerMovementComponent::accelerate_horizontally(Vector2 dir, float deltaTime) {
	velocity.x = dir.x > 0.0f ? max_run_speed : -max_run_speed;
	facing_dir = dir;
}

void PlayerMovementComponent::decelerate_horizontally(float deltaTime) {
	velocity.x = 0.0f;
}

void PlayerMovementComponent::jump() {
	velocity.y = -120.0f;
}

bool PlayerMovementComponent::is_falling() const {
	ERR_FAIL_NULL_V(player, false);
	return !player->is_on_floor() && velocity.y > 0.0f;
}
