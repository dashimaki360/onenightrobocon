#include "ev3api.h"
#include "inc/main.h"
#include "inc/tonnel.h"
#include "inc/lcd.h"

static const int is_pressed_steer = -30;
static const int not_pressed_steer = 45;
static const int def_power = -40;
static int steer = 0;

static Status st = {
  .mode = "TONNEL",
  .option[0] = "foo",
  .option[1] = "bar",
  .option[2] = "hoge",
};


static int will_update_lcd = true;

void tnl_run(void){
  //get touch senser val
  int is_pressed = ev3_touch_sensor_is_pressed(touch_sensor);
  int power = def_power;
  if(is_pressed){
    ev3_motor_set_power(left_motor,0);
    ev3_motor_set_power(right_motor,40);
    steer = 0;
  }else{
    if(steer < 30){
      steer += 2;
    }
	  ev3_motor_steer(left_motor,right_motor,power, steer);
  }
  sprintf(st.option[0], "power %03d", power);
  sprintf(st.option[1], "steer %03d", steer);
  will_update_lcd = true;


  //if upsate run status, show it to lcd
  if(will_update_lcd){
    lcd_show_run_st(st);
    will_update_lcd = false;
  }
  return;
}


