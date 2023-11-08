#ifndef PLAYER_H
#define PLAYER_H

using namespace godot;

class PlayerMovementFSMComponent;
class PlayerMovementComponent;
class PlayerControllerComponent;

class Player : public CharacterBody2D {
	GDCLASS(Player, CharacterBody2D);

public:
	Player();

protected:
	static void _bind_methods();

private:
	Camera2D* camera = nullptr;
	AnimationPlayer* back_arm = nullptr;
	AnimationPlayer* leg = nullptr;
	AnimationPlayer* torso = nullptr;
	AnimationPlayer* head = nullptr;
	AnimationPlayer* front_arm = nullptr;

	PlayerMovementFSMComponent* movement_fsm = nullptr;
	PlayerMovementComponent* movement = nullptr;
	PlayerControllerComponent* controller = nullptr;

	// replicates
	int32_t uid;

public:
	_FORCE_INLINE_ Camera2D* get_camera() const { return camera; }
	_FORCE_INLINE_ PlayerMovementFSMComponent* get_movement_fsm() const { return movement_fsm; }
	_FORCE_INLINE_ PlayerMovementComponent* get_movement() const { return movement; }
	_FORCE_INLINE_ PlayerControllerComponent* get_controller() const { return controller; }
	_FORCE_INLINE_ int32_t get_uid() const { return uid; }
	void set_camera(Camera2D* p_camera);
	void set_movement_fsm(PlayerMovementFSMComponent* p_movement_fsm);
	void set_movement(PlayerMovementComponent* p_movement);
	void set_controller(PlayerControllerComponent* p_controller);
	void set_uid(int32_t p_uid);

	// ------------------------------------------

public:
	virtual void _ready() override;
	virtual void _process(double delta) override;
	virtual void _physics_process(double delta) override;
	virtual void _unhandled_input(const Ref<InputEvent>& event) override;
};

#endif // PLAYER_H
