#ifndef PLAYERMOVEMENTCOMPONENT
#define PLAYERMOVEMENTCOMPONENT

#include <godot_cpp/classes/node.hpp>

#include "pp.h"

using namespace godot;

class Player;

class PlayerMovementComponent : public Node {
	GDCLASS(PlayerMovementComponent, Node)

protected:
	static void _bind_methods();

public:
	virtual void _ready() override;

//~Begin This Class
public:
	// call from other
	void move();
	void apply_gravity(float deltaTime);
	void accelerate_horizontally(Vector2 dir, float deltaTime);
	void decelerate_horizontally(float deltaTime);
	void jump();
	bool is_falling() const;

	// getter
	_FORCE_INLINE_ Vector2 get_facing_dir() const { return facing_dir; }

private:
	// setting
	void set_max_run_speed(real_t p_speed);
	real_t get_max_run_speed() const;

	// run
	real_t max_run_speed = 8.0f * 16.0f;

	Player* player = nullptr;
	Vector2 velocity = Vector2(0.0f, 0.0f);
	Vector2 facing_dir = Vector2(1.0f, 0.0f);
};

#endif // PLAYERMOVEMENTCOMPONENT
