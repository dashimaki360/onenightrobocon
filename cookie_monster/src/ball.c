#include "ev3api.h"
#include "inc/main.h"
#include "inc/ball.h"

void ball_run(void){

	//display
    char msg[256]= {0};
	sprintf(msg, "Put the ball in the goal");
    ev3_lcd_draw_string(msg,0,20);

    //medium motor rotate
    ev3_motor_rotate(medium_motor,rotate_angle,rotate_speed,false);

    //if motor stoped before reach rotate_angle, the motor stop
    int now_count = ev3_motor_get_counts(medium_motor);
    int pre_count;
    do {
    	pre_count = now_count;
    	//sleep　10[ms]
    	tslp_tsk(10);
    	now_count = ev3_motor_get_counts(medium_motor);
    	}while(pre_count != now_count);
    ev3_motor_set_power(medium_motor,0);

	return;
}


