#include "ev3api.h"
#include "inc/initialize.h"
#include "inc/mode_checker.h"

static const int MODE_NUM = END;
static int bt = -1;
static int mode = START;

static int get_pressed_button(void);
static int update_mode(void);
static int update_lcd(void);
static int pressed_start_button();

void init_task(intptr_t exinf){

  update_lcd();
  //select start mode
  while(true){
    get_pressed_button();
    update_mode();
    update_lcd();
    if( pressed_start_button() ){
      //TODO
      //mc_set_init_mode();
      ev3_lcd_draw_string("start!!",0,40);
      break;
    }
  }
  //change initflag to finish

  set_flg(INIT_FLG, 0x01);
  ev3_lcd_draw_string("finish init",0,60);
}

int get_pressed_button(void){
  while(1){
    if (ev3_button_is_pressed(UP_BUTTON)) {
      while(ev3_button_is_pressed(UP_BUTTON));
      bt = UP_BUTTON;
      break;
    }
    if (ev3_button_is_pressed(DOWN_BUTTON)) {
      while(ev3_button_is_pressed(DOWN_BUTTON));
      bt = DOWN_BUTTON;
      break;
    }
    if (ev3_button_is_pressed(ENTER_BUTTON)) {
      while(ev3_button_is_pressed(ENTER_BUTTON));
      bt = ENTER_BUTTON;
      break;
    }
    if (ev3_button_is_pressed(BACK_BUTTON)) {
      while(ev3_button_is_pressed(BACK_BUTTON));
      bt = BACK_BUTTON;
    }
  }
  return 0;
}

int update_mode(void){
  if(bt < 0||bt > TNUM_BUTTON){
    return 1;
  }

  switch(bt){
    case UP_BUTTON:
      mode++;
      break;
    case DOWN_BUTTON:
      mode--;
      break;
    case ENTER_BUTTON:
      break;
    case BACK_BUTTON:
      // no use now
      break;
    default:
      break;
  }
  mode = (mode+MODE_NUM) % MODE_NUM;
  return 0;
}

int update_lcd(void){
  char msg[128]= {0};

  switch(mode){
    case START:
      sprintf(msg, "MODE: START     ");
      break;
    case FLAT:
      sprintf(msg, "MODE: FLAT      ");
      break;
    case BRIDGE:
      sprintf(msg, "MODE: BRIDGE    ");
      break;
    case DISPLAY:
      sprintf(msg, "MODE: DISPLAY   ");
      break;
    case TONNEL:
      sprintf(msg, "MODE: TONNEL    ");
      break;
    case BALL:
      sprintf(msg, "MODE: BALL      ");
      break;
    case END:
      //this mode is err
      sprintf(msg, "MODE: END       ");
      break;
    default:
      //this mode is err
      sprintf(msg, "MODE: DEFAULT   ");
      break;
  }
  ev3_lcd_draw_string(msg,0,20);
  sprintf(msg, "%d",mode);
  ev3_lcd_draw_string(msg,0,40);
  return 0;
}

int pressed_start_button(){
  switch(bt){
    case ENTER_BUTTON:
      return 1;
      break;
    default:
      break;
  }
  return 0;
}

