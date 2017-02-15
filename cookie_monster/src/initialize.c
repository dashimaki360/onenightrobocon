#include "ev3api.h"
#include "inc/initialize.h"
#include "inc/mode_checker.h"
//#include "kernel_cfg.h"

static const int MODE_NUM = END;
static int bt=0;
static int mode = START;

static int get_pressed_button(void);
static int update_mode(void);
static int update_lcd(void);
static int pressed_start_button();

void init_task(intptr_t exinf){

  //select start mode
  while(true){
    get_pressed_button();
    update_mode();
    update_lcd();
    if( pressed_start_button() ){
      //TODO
      //mc_set_init_mode();
      break;
    }
    tslp_tsk(30);
  }


  //change initflag to finish
  set_flg(INIT_FLG, 0x01);
}

int get_pressed_button(void){
  return 0;
}

int update_mode(void){
  mode ++;
  mode = mode % MODE_NUM;
  return 0;
}
int update_lcd(void){
  ev3_lcd_draw_string("hogehoge initialized",0,20);
  return 0;
}

int pressed_start_button(){
  return 0;
}

