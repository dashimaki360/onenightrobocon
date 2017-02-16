#include "ev3api.h"
#include "inc/main.h"
#include "inc/flat.h"

static const float delta_t = 0.001;
static const float st_p = 2;
static const float st_i = 0;
static const float st_d = 0;
static float lasterror = 0, integral = 0;
static float midpoint = (100 - 0) / 2 + 0;

void flat_run(void){
	float error = midpoint - ev3_color_sensor_get_reflect(line_sensor);
	//float error = midpoint - ev3_color_sensor_get_ambient(color_sensor);
	error = error;
	integral += error * delta_t;
	float steer = st_p * error + st_i * integral + st_d * (error - lasterror)/delta_t;
	//debug
	char msg[128] = {};
	sprintf(msg, "err %4f steer %4f inte %4f", error, steer, integral);
	ev3_lcd_draw_string(msg,0,40);

	ev3_motor_steer(left_motor, right_motor, -40, steer);
	lasterror = error;
	tslp_tsk(1);
  return;
}


