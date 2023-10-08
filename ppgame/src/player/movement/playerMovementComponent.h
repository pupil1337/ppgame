#ifndef PLAYERMOVEMENTCOMPONENT
#define PLAYERMOVEMENTCOMPONENT

#include <scene/main/node.h>

class PlayerMovementComponent : public Node {
	GDCLASS(PlayerMovementComponent, Node)

protected:
	static void _bind_methods();

//~Begin This Class
private:
	// setting
	void set_max_run_speed(real_t p_speed);
	real_t get_max_run_speed() const;

	// run
	real_t max_run_speed = 16.0f;
};

#endif // PLAYERMOVEMENTCOMPONENT
