#ifndef PLAYERMOVEMENTCOMPONENT
#define PLAYERMOVEMENTCOMPONENT

using namespace godot;

class Player;

class PlayerMovementComponent : public Node {
	GDCLASS(PlayerMovementComponent, Node)

protected:
	static void _bind_methods();

private:
	Player* player = nullptr;

	float max_run_speed = 8.0f * 16.0f;

public:
	_FORCE_INLINE_ Player* get_player() const { return player; }
	_FORCE_INLINE_ float get_max_run_speed() const { return max_run_speed; }
	void set_player(Player* p_player);
	void set_max_run_speed(float p_max_run_speed);

	// ------------------------------------------

public:
	void move();
	void apply_gravity(float deltaTime);
	void accelerate_horizontally(Vector2 dir, float deltaTime);
	void decelerate_horizontally(float deltaTime);
	void jump();
	bool is_falling() const;

	_FORCE_INLINE_ Vector2 get_facing_dir() const { return facing_dir; }

private:
	Vector2 velocity;
	Vector2 facing_dir = Vector2(1.0f, 0.0f);
};

#endif // PLAYERMOVEMENTCOMPONENT
