#include "finiteStateMachine.h"

void FiniteStateMachine::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_READY: {
			print_line("FiniteStateMachine:: NOTIFICATION_READY");
		} break;
	}
}