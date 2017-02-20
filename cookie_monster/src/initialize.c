#include "ev3api.h"
#include "inc/initialize.h"
#include "inc/mode_checker.h"
#include "inc/lcd.h"
#include "inc/main.h"

static const int MODE_NUM = END;
static int bt = -1;
static Menu mn={
  .pos=0,
  .num=4,
  .title[0]="MODE",
    .param_pos[0]=0,
    .param_num[0]=END,
    .param[0][0]="START",
    .param[0][1]="FLAT1",
    .param[0][2]="BRIDGE",
    .param[0][3]="FLAT2",
    .param[0][4]="DISPLAY",
    .param[0][5]="FLAT3",
    .param[0][6]="TONNEL",
    .param[0][7]="FLAT4",
    .param[0][8]="BALL",

  .title[1]="MODE FIX",
    .param_pos[1]=0,
    .param_num[1]=2,
    .param[1][0]="No",
    .param[1][1]="Yes",

  .title[2]="PARAM SET",
    .param_pos[2]=0,
    .param_num[2]=1,
    .param[2][0]=" ",

  .title[3]="RUN",
    .param_pos[3]=0,
    .param_num[3]=1,
    .param[3][0]=" ",
};

static int get_pressed_button(void);
static int update_mode();
static int update_lcd(Menu mn);
static int pressed_start_button();

void init_task(intptr_t exinf){
  lcd_set_font_size();
  lcd_show_boot_logo();

  //sensor モーター ポートを設定 
  ev3_motor_config(left_motor, LARGE_MOTOR);
  ev3_motor_config(right_motor, LARGE_MOTOR);
  ev3_motor_config(medium_motor, MEDIUM_MOTOR);
  ev3_sensor_config(touch_sensor, TOUCH_SENSOR);
  ev3_sensor_config(color_sensor, COLOR_SENSOR);
  ev3_sensor_config(line_sensor, COLOR_SENSOR);
  ev3_sensor_config(u_sonic_sensor, ULTRASONIC_SENSOR);

  update_lcd(mn);
  //select start mode
  while(true){
    get_pressed_button();
    update_mode();
    update_lcd(mn);
    if( pressed_start_button() ){
      if(3==mn.pos){
        mc_set_init_mode(mn.param_pos[0]);
        //set mode fix
        if(mn.param_pos[1]==1){
          mc_set_mode_fix();
        }else{
          mc_release_mode_fix();
        }
      break;
      }
    }
  }
  //change initflag to finish
  set_flg(INIT_FLG, 0x01);
  return;
}

int get_pressed_button(void){
  while(1){
    if (ev3_button_is_pressed(LEFT_BUTTON)) {
      while(ev3_button_is_pressed(LEFT_BUTTON));
      bt = LEFT_BUTTON;
      break;
    }
    if (ev3_button_is_pressed(RIGHT_BUTTON)) {
      while(ev3_button_is_pressed(RIGHT_BUTTON));
      bt = RIGHT_BUTTON;
      break;
    }
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

int update_mode(){
  if(bt < 0||bt > TNUM_BUTTON){
    return 1;
  }

  switch(bt){
    case LEFT_BUTTON:
      mn.param_pos[mn.pos]--;
      break;
    case RIGHT_BUTTON:
      mn.param_pos[mn.pos]++;
      break;
    case UP_BUTTON:
      mn.pos--;
      break;
    case DOWN_BUTTON:
      mn.pos++;
      break;
    default:
      break;
  }
  mn.pos = (mn.pos+mn.num) % mn.num;
  mn.param_pos[mn.pos] = (mn.param_pos[mn.pos] + mn.param_num[mn.pos]) % mn.param_num[mn.pos];
  return 0;
}

int update_lcd(Menu mn){
  lcd_show_menu(mn);
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

