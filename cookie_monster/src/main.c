/**
 * Cookie Monster
 * One Nught ROBOCON couse test project
 */

#include "ev3api.h"
#include "inc/main.h"
#include "inc/mode_checker.h"
#include "inc/flat.h"
#include "inc/bridge.h"
#include "inc/display.h"
#include "inc/tonnel.h"
#include "inc/ball.h"

//メインタスク
void main_task(intptr_t unused) {
  //wait finish initialized
  FLGPTN flag;
  wai_flg(INIT_FLG, 0x01, TWF_ANDW, &flag);

  //sensor モーター ポートを設定 
  ev3_motor_config(left_motor, LARGE_MOTOR);
  ev3_motor_config(right_motor, LARGE_MOTOR);
  ev3_sensor_config(touch_sensor, TOUCH_SENSOR);
  ev3_sensor_config(color_sensor, COLOR_SENSOR);
  ev3_sensor_config(u_sonic_sensor, ULTRASONIC_SENSOR);

  Mode mode = START;
  while(true){
    mode = mc_get_mode();
    switch(mode) {
      case START:
        break;
      case FLAT:
        flat_run();
        break;
      case BRIDGE:
        brg_run();
        break;
      case DISPLAY:
        disp_run();
        break;
      case TONNEL:
        tnl_run();
        break;
      case BALL:
        ball_run();
        break;
      default:
        break;
    }
  }

  return;
}
