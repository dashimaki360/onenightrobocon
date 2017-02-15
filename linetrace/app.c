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
    // Register button handlers
    ev3_button_set_on_clicked(BACK_BUTTON, button_clicked_handler, BACK_BUTTON);

    // Configure motors
    ev3_motor_config(left_motor, LARGE_MOTOR);
    ev3_motor_config(right_motor, LARGE_MOTOR);

    // Configure sensors
    ev3_sensor_config(touch_sensor, TOUCH_SENSOR);
    ev3_sensor_config(color_sensor, COLOR_SENSOR);

    /**
     * Calibrate for light intensity of WHITE
     */
    ev3_speaker_play_tone(NOTE_C4, 100);
    tslp_tsk(100);
    ev3_speaker_play_tone(NOTE_C4, 100);
    // TODO: Calibrate using maximum mode => 100
    ev3_lcd_draw_string("Press the touch sensor mger WHITE.",0,0);
    while(!ev3_touch_sensor_is_pressed(touch_sensor));
    while(ev3_touch_sensor_is_pressed(touch_sensor));
    int white = ev3_color_sensor_get_reflect(color_sensor);
    //int white = ev3_color_sensor_get_ambient(color_sensor);
    char msg[256]= {0};
    sprintf(msg, "white %d", white);
    ev3_lcd_draw_string(msg,0,0);

    /**
     * Calibrate for light intensity of BLACK
     */
    ev3_speaker_play_tone(NOTE_C4, 100);
    tslp_tsk(100);
    ev3_speaker_play_tone(NOTE_C4, 100);
    // TODO: Calibrate using maximum mode => 100
    // TODO: Calibrate using minimum mode => 0
    ev3_lcd_draw_string("Press the touch sensor mger BLACK.\n",0,20);
    while(!ev3_touch_sensor_is_pressed(touch_sensor));
    while(ev3_touch_sensor_is_pressed(touch_sensor));
    int black = ev3_color_sensor_get_reflect(color_sensor);
    //int black = ev3_color_sensor_get_ambient(color_sensor);
    sprintf(msg, "black %d", black);
    ev3_lcd_draw_string(msg,0,20);

    /**
     * PID controller
     */
    const float delta_t = 0.001;
    const float st_p = 2;
    const float st_i = 0;
    const float st_d = 0;
    float lasterror = 0, integral = 0;
    float midpoint = (white - black) / 2 + black;
    while (1) {
        float error = midpoint - ev3_color_sensor_get_reflect(color_sensor);
        //float error = midpoint - ev3_color_sensor_get_ambient(color_sensor);
        error = error;
        integral += error * delta_t;
        float steer = st_p * error + st_i * integral + st_d * (error - lasterror)/delta_t;
        //debug
        sprintf(msg, "err %4f steer %4f inte %4f", error, steer, integral);
        ev3_lcd_draw_string(msg,0,40);

        ev3_motor_steer(left_motor, right_motor, -40, steer);
        lasterror = error;
        tslp_tsk(1);
    }
}
