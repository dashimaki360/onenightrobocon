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
        //fast_flat_run();
        break;
      case FLAT1:
        fast_flat_run();
        break;
      case BRIDGE:
        fast_flat_run();
        break;
      case FLAT2:
        fast_flat_run();
        break;
      case DISPLAY:
        disp_run();
        break;
      case FLAT3:
        fast_flat_run();
        break;
      case TONNEL:
        tnl_run();
        break;
      case FLAT4:
        after_tnl_flat_run();
        break;
      case BALL:
        ball_run();
        break;
      default:
        break;
    }
    tslp_tsk(30);
  }

  return;
}
