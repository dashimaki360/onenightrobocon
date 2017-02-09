#include "ev3api.h"
#include "inc/initialize.h"
//#include "kernel_cfg.h"

void init_task(intptr_t exinf){

  //hoge hoge sample
  ev3_lcd_draw_string("hogehoge initialiging",0,0);
  tslp_tsk(2000);
  ev3_lcd_draw_string("hogehoge initialized",0,20);

  //change initflag to finish
  set_flg(INIT_FLG, 0x01);
}

