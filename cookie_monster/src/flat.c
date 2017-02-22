#include "ev3api.h"
#include "inc/main.h"
#include "inc/flat.h"
#include "inc/lcd.h"

static const float delta_t = 0.001;
static const float st_p = 2;
static const float st_i = 0;
static const float st_d = 0;

static float lasterror = 0, integral = 0;
static float midpoint = (100 - 0) / 2 + 0;
static int will_update_lcd = true;

static Status st = {
  .mode = "FLAT",
  .option[0] = "foo",
  .option[1] = "bar",
  .option[2] = "hoge",
};

void flat_run(void){
	float error = midpoint - ev3_color_sensor_get_reflect(line_sensor);
	error = error;
	integral += error * delta_t;
	float steer = st_p * error + st_i * integral + st_d * (error - lasterror)/delta_t;
	//debug
  sprintf(st.option[0], "error %4f", error);
  sprintf(st.option[1], "steer %4f", steer);
  will_update_lcd = true;

	ev3_motor_steer(left_motor, right_motor, -40, steer);
	lasterror = error;

  //if upsate run status, show it to lcd
  if(will_update_lcd){
    lcd_show_run_st(st);
    will_update_lcd = false;
  }
  return;
}


