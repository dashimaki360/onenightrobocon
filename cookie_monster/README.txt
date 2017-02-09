How To Use and Development "Cookie Monster"

#file tree
cookie_monster
  +inc
  | +main.h
  | +initializer.h
  | +mode_checker.h
  | +flat.h
  | +bridge.h
  | +display.h
  | +tonnel.h
  | +ball.h
  |
  +src
  | +main.c
  | +initializer.c
  | +mode_checker.c
  | +flat.c
  | +bridge.c
  | +display.c
  | +tonnel.c
  | +ball.c
  |
  +app.c
  +app.cfg
  +Makefile.inc


please devide file and use "static"
Don't use global variable

name roule
global method name please use prefix 
  ex) disp_run();
  ex) mc_get_mode();

local val or method use static
  ex) static int count = 0;
      static bool is_touch_wall();


#How To make
$cd /{YOUR_ENV_PATH}/onenightrobocon/
$make app=cookie_monster

bin file is at /onenightrobocon/buid/cookie_monster

Lets Enjoy XD
