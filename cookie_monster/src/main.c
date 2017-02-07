#include "ev3api.h"
#include "inc/main.h"

/**
 * Define the connection ports of the sensors and motors.
 * By default, this application uses the following ports:
 * Touch sensor: Port 2
 * Color sensor: Port 3
 * Left motor:   Port B
 * Right motor:  Port C
 */
const int touch_sensor = EV3_PORT_2, color_sensor = EV3_PORT_3, left_motor = EV3_PORT_B, right_motor = EV3_PORT_C;


void main_task(intptr_t unused) {

  // Configure motors
  ev3_motor_config(left_motor, LARGE_MOTOR);
  ev3_motor_config(right_motor, LARGE_MOTOR);

  // Configure sensors
  ev3_sensor_config(touch_sensor, TOUCH_SENSOR);
  ev3_sensor_config(color_sensor, COLOR_SENSOR);

  int reflect_val = ev3_color_sensor_get_reflect(color_sensor);
  char msg[256]= {0};
  sprintf(msg, "reflect_val %03d", reflect_val);
  ev3_lcd_draw_string(msg,0,20);

  return;
}
