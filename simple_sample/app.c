/**
 * This sample program shows a PID controller for line following.
 *
 * Robot construction: Educator Vehicle
 *
 * References:
 * http://robotsquare.com/wp-content/uploads/2013/10/45544_educator.pdf
 * http://thetechnicgear.com/2014/03/howto-create-line-following-robot-using-mindstorms/
 */

#include "ev3api.h"
#include "app.h"

#define DEBUG

#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

/**
 * Define the connection ports of the sensors and motors.
 * By default, this application uses the following ports:
 * Touch sensor: Port 2
 * Color sensor: Port 3
 * Left motor:   Port B
 * Right motor:  Port C
 */
const int touch_sensor = EV3_PORT_2, color_sensor = EV3_PORT_3, left_motor = EV3_PORT_B, right_motor = EV3_PORT_C;

static void button_clicked_handler(intptr_t button) {
    switch(button) {
    case BACK_BUTTON:
#if !defined(BUILD_MODULE)
        syslog(LOG_NOTICE, "Back button clicked.");
#endif
        break;
    }
}

void main_task(intptr_t unused) {

  // Configure motors
  ev3_motor_config(left_motor, LARGE_MOTOR);
  ev3_motor_config(right_motor, LARGE_MOTOR);

  // Configure sensors
  ev3_sensor_config(touch_sensor, TOUCH_SENSOR);
  ev3_sensor_config(color_sensor, COLOR_SENSOR);

  while(1){
    int reflect_val = ev3_color_sensor_get_reflect(color_sensor);

    char msg[256]= {0};
    sprintf(msg, "reflect_val %03d", reflect_val);
    ev3_lcd_draw_string(msg,0,20);

    int steer = 0;
    int power = 50;
    ev3_motor_steer(left_motor, right_motor, power, steer);

    tslp_tsk(1); //[ms]
  }

  return;
}
