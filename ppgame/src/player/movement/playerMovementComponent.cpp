#include "playerMovementComponent.h"

#include "player/player.h"

void PlayerMovementComponent::_bind_methods() {
	ADD_GROUP("Run", "run_");
	ClassDB::bind_method(D_METHOD("set_max_run_speed", "speed"), &PlayerMovementComponent::set_max_run_speed);
	ClassDB::bind_method(D_METHOD("get_max_run_speed"), &PlayerMovementComponent::get_max_run_speed);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_run_speed", PROPERTY_HINT_RANGE, "0.01,1920.0,0.01,or_greater,suffix:px"), "set_max_run_speed", "get_max_run_speed");
}

void PlayerMovementComponent::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_READY: {
			player = Object::cast_to<Player>(get_parent());
		} break;
	}
}

void PlayerMovementComponent::move() {
	if (player) {
		player->set_velocity(velocity);
		player->move_and_slide();
	}
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
	return !player->is_on_floor() && velocity.y > 0.0f;
}

// setting --------------------------------------------------------------------
void PlayerMovementComponent::set_max_run_speed(real_t p_speed) {
	ERR_FAIL_COND(p_speed <= 0.0f);
	max_run_speed = p_speed;
}

real_t PlayerMovementComponent::get_max_run_speed() const {
	return max_run_speed;
}
