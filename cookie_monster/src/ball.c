#include "ev3api.h"
#include "inc/main.h"
#include "inc/ball.h"
#include "inc/lcd.h"

static int f_flag = 0;

static Status st = {
  .mode = "BALL",
  .option[0] = "foo",
  .option[1] = "bar",
  .option[2] = "hoge",
};

void ball_run(void){
    if(0 == f_flag){
        ev3_motor_steer(left_motor, right_motor, 0, 0);
        //display
        sprintf(st.option[0], "Put the ball in the goal");
        lcd_show_run_st(st);

        //medium motor rotate
        ev3_motor_rotate(medium_motor,rotate_angle,rotate_speed,false);

        //if motor stoped before reach rotate_angle, the motor stop
        /*int now_count = ev3_motor_get_counts(medium_motor);
        int pre_count;
        do {
            pre_count = now_count;
            //sleep　10[ms]
            tslp_tsk(10);
            now_count = ev3_motor_get_counts(medium_motor);
            }while(pre_count != now_count);
        ev3_motor_set_power(medium_motor,0);*/
        f_flag = 1;
    }

	return;
}


