/**
 * MODE CHECKER
 */

#include "ev3api.h"
#include "inc/main.h"
#include "inc/mode_checker.h"

           
static Mode mode = START;

static colorid_t pre_color_id = COLOR_WHITE;

//mode check cycle task
void mc_cyc(intptr_t unused) {

  //wait finish initialized
  FLGPTN flag;
  wai_flg(INIT_FLG, 0x01, TWF_ANDW, &flag);

  mc_update_mode();
  return;
}

Mode mc_get_mode(){
  return mode;
}

void mc_update_mode(){
  colorid_t color_id = ev3_color_sensor_get_color(color_sensor);
  
  if(COLOR_RED != color_id && COLOR_RED == pre_color_id){		//mode change beyond red line
  	  mode++;
  	  if(mode > END) mode = END;
  	 
  }
  
  if(ev3_touch_sensor_is_pressed(touch_sensor)){
  	  mode = BALL;
  }
  
  pre_color_id = color_id;
}

void mc_set_init_mode(Mode set_mode){
  if(set_mode < 0 || set_mode > END) return;
  mode = set_mode;
  return;
}
