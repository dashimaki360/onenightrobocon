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

static int will_update_lcd = true;

void tnl_run(void){
  if(will_update_lcd){
    lcd_show_run_st(st);
    will_update_lcd = false;
  }
	//ev3_motor_steer(left_motor,right_motor,-30, 0);
  return;
}


