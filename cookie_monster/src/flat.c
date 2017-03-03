#include "ev3api.h"
#include "inc/main.h"
#include "inc/flat.h"
#include "inc/lcd.h"

static const float delta_t = 0.001;
static const float st_p = 2;
static const float st_i = 0;
static const float st_d = 0;

static float lasterror = 0, integral = 0;
static float midpoint = (80 - 7) / 2 + 0;
static int will_update_lcd = true;
static int is_after_tnl_online = false;
static int is_rotating = false;

static Status st = {
  .mode = "FLAT",
  .option[0] = "foo",
  .option[1] = "bar",
  .option[2] = "hoge",
};

void flat_run(void){
	float error = midpoint - ev3_color_sensor_get_reflect(line_sensor);
	error = error;
	float steer = st_p * error;// + st_d * (error - lasterror)/delta_t;
	//debug
  sprintf(st.option[0], "error %4f", error);
  sprintf(st.option[1], "steer %4f", steer);
  will_update_lcd = true;

	ev3_motor_steer(left_motor, right_motor, -50, steer);
	lasterror = error;

  //if upsate run status, show it to lcd
  if(will_update_lcd){
    lcd_show_run_st(st);
    will_update_lcd = false;
  }
  return;
}

void fast_flat_run(void){
  float error = midpoint - ev3_color_sensor_get_reflect(line_sensor);
  error = error;
  integral += error * delta_t;
  float steer =  1 * error + 3 * (error - lasterror);
  //debug
  sprintf(st.option[0], "error %4f", error);
  sprintf(st.option[1], "steer %4f", steer);
  will_update_lcd = true;

  ev3_motor_steer(left_motor, right_motor, -80, steer);
  lasterror = error;

  //if upsate run status, show it to lcd
  if(will_update_lcd){
    lcd_show_run_st(st);
    will_update_lcd = false;
  }
  return;
}

void after_tnl_flat_run(void){
  if(is_after_tnl_online){
  //online
    //flat_run();
    fast_flat_run();
    sprintf(st.option[2], "online");
    will_update_lcd = true;
  }else{
  //off line
	  int reflect = ev3_color_sensor_get_reflect(line_sensor);
    if(is_rotating){
    //roatting
      ev3_motor_set_power(left_motor,20);
      ev3_motor_set_power(right_motor,-20);
      if(reflect > 75){
        is_rotating = false;
        is_after_tnl_online = true;
      }
      sprintf(st.option[2], "rotating %03d",reflect);
      will_update_lcd = true;
    }else{
    //finding line
	    ev3_motor_steer(left_motor,right_motor,-30, -45);
      if(reflect < 20){
        is_rotating = true;
      }
      sprintf(st.option[2], "find line %03d",reflect);
      will_update_lcd = true;
    }
  }
  if(will_update_lcd){
    lcd_show_run_st(st);
    will_update_lcd = false;
  }
  return;
}

