#include "playerMovementComponent.h"

void PlayerMovementComponent::_bind_methods() {
	ADD_GROUP("Run", "run_");
	ClassDB::bind_method(D_METHOD("set_max_run_speed", "speed"), &PlayerMovementComponent::set_max_run_speed);
	ClassDB::bind_method(D_METHOD("get_max_run_speed"), &PlayerMovementComponent::get_max_run_speed);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_run_speed", PROPERTY_HINT_RANGE, "0.01,1920.0,0.01,or_greater,suffix:px"), "set_max_run_speed", "get_max_run_speed");
}

// setting --------------------------------------------------------------------
void PlayerMovementComponent::set_max_run_speed(real_t p_speed) {
	ERR_FAIL_COND(p_speed <= 0.0f);
	max_run_speed = p_speed;
}

real_t PlayerMovementComponent::get_max_run_speed() const {
	return max_run_speed;
}
