#include "ev3api.h"
#include "inc/main.h"
#include "inc/display.h"
#include "inc/lcd.h"

static void  disp_mode(void);
static void  disp_flat_mode(void);

static const float delta_t = 0.001;
static float lasterror = 0, integral = 0;
<<<<<<< HEAD
static float midpoint_d = (20 - 0) / 2 + 0;
=======
static float midpoint_d = (25 - 0) / 2 + 0;
>>>>>>> a20fab98ad2cfaaa26eafd3bab3cb48ff03b3f1d
static float midpoint_f = (100 - 0) / 2 + 0;
static int will_update_lcd = true;
static int mode = false;


static Status st = {
  .mode = "DISPLAY",
  .option[0] = "foo",
  .option[1] = "bar",
  .option[2] = "hoge",
};

void disp_run(void){
  float color_sensor_point = ev3_color_sensor_get_reflect(color_sensor);
  if(20 > color_sensor_point){
    disp_mode();
    mode = true;
  }else{
    disp_flat_mode();
    mode = false;
  }
  //update lcd
  if(will_update_lcd){
    lcd_show_run_st(st);
    will_update_lcd = false;
  }
  return;
}
void disp_mode(void){
<<<<<<< HEAD
  float st_p = 5;  
=======
  float st_p = 7;  
>>>>>>> a20fab98ad2cfaaa26eafd3bab3cb48ff03b3f1d
  float st_i = 0;
  float st_d = 0;
  float error = midpoint_d - ev3_color_sensor_get_ambient(line_sensor);
  if(false == mode) integral = 0;

  error = error*5;
  integral += error * delta_t;
  float steer = st_p * error + st_i * integral + st_d * (error - lasterror)/delta_t;
  //debug
  sprintf(st.option[0], "error %4f", error);
  sprintf(st.option[1], "steer %4f", steer);
  will_update_lcd = true;
  ev3_motor_steer(left_motor, right_motor, -15, steer);
  lasterror = error;
}
void disp_flat_mode(void){
  float st_p = 2;  
  float st_i = 0;
  float st_d = 0;
  float error = midpoint_f - ev3_color_sensor_get_reflect(line_sensor);
  if(true == mode) integral = 0;
  error = error;
  integral += error * delta_t;
  float steer = st_p * error + st_i * integral + st_d * (error - lasterror)/delta_t;
  //debug
  sprintf(st.option[0], "error %4f", error);
  sprintf(st.option[1], "steer %4f", steer);
  will_update_lcd = true;
  ev3_motor_steer(left_motor, right_motor, -30, steer);
  lasterror = error;

}




