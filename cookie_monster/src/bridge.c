#include "ev3api.h"
#include "inc/bridge.h"

void brg_run(void){
	ev3_motor_steer(left_motor,right_motor,-30, 0);
  	return;
}


