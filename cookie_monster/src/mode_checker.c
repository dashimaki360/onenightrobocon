/**
 * MODE CHECKER
 */

#include "ev3api.h"
#include "inc/mode_checker.h"

           
static Mode mode = START;

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
}
