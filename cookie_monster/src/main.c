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

void main_task(intptr_t unused) {
  //wait finish initialized
  FLGPTN flag;
  wai_flg(INIT_FLG, 0x01, TWF_ANDW, &flag);

  Mode mode = START;
  while(true){
    mode = mc_get_mode();
    switch(mode) {
      case START:
        //for debug test
        //ev3_lcd_draw_string("main start mode now",0,40);
        break;
      case FLAT1:
        flat_run();
        break;
      case FLAT2:
        flat_run();
        break;
      case FLAT3:
        flat_run();
        break;
      case FLAT4:
        flat_run();
        break;
      case BRIDGE:
        flat_run();
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
    tslp_tsk(50);
  }

  return;
}
