#include "ev3api.h"
#include "inc/main.h"
#include "inc/tonnel.h"
#include "inc/lcd.h"

static Status st = {
  .mode = "TONNEL",
  .option[0] = "foo",
  .option[1] = "bar",
  .option[2] = "hoge",
};

static const is_pressed_steer = -10;
static const not_pressed_steer = 20;
static const def_power = -30;

static int will_update_lcd = true;

void tnl_run(void){
  //if upsate run status, show it to lcd
  if(will_update_lcd){
    lcd_show_run_st(st);
    will_update_lcd = false;
  }
  //get touch senser val
  int steer = 0;
  int is_pressed = ev3_touch_sensor_is_pressed(touch_sensor)
  int power = def_power;
  if(is_pressed){
    steer = is_pressed_steer;
  }else{
    steer = not_pressed_steer;
  }

	ev3_motor_steer(left_motor,right_motor,power, steer);
  return;
}


