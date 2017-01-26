/**
 * TOPPERS/EV3　サンプル　「黒い線に沿って進む」.
 * 動作説明　　黒い線に沿って進む。止まることはない。
 */

#include "ev3api.h"
#include "app.h"

/**
 * ポートの接続対応
 * Touch sensor: Port 2 //今回は未使用
 * Color sensor: Port 3
 * USonic sensor: Port 4 //今回は未使用
 * Left  motor:  Port B
 * Right motor:  Port C
 */
const int touch_sensor = EV3_PORT_2;
const int color_sensor = EV3_PORT_3;
const int u_sonic_sensor = EV3_PORT_4;
const int left_motor = EV3_PORT_B;
const int right_motor = EV3_PORT_C;

void main_task(intptr_t unused) {
  //モーターポートを設定 
  ev3_motor_config(left_motor, LARGE_MOTOR);
  ev3_motor_config(right_motor, LARGE_MOTOR);

  //センサーポートを設定
  ev3_sensor_config(touch_sensor, TOUCH_SENSOR);
  ev3_sensor_config(color_sensor, COLOR_SENSOR);
  ev3_sensor_config(u_sonic_sensor, ULTRASONIC_SENSOR);


  const int mid_point = 50; //白と黒の閾値
  const int power = 50;  //モーターパワーj
  int steer = 0;  //ハンドル操作量


  while(1){
    //明るさ取得
    int reflect_val = ev3_color_sensor_get_reflect(color_sensor);

    //ハンドル操作量決定
    if(reflect_val > mid_point){ //白い
      steer = 30;
    }else{  //黒い
      steer = -30;
    }

    //モータ操作量をセット
    ev3_motor_steer(left_motor, right_motor, power, steer);

    //明るさとハンドル操作量を表示
    char msg[256]= {0};
    sprintf(msg, "reflect_val:%03d steer:%03d", reflect_val, steer);
    ev3_lcd_draw_string(msg,0,20);

    tslp_tsk(1); //スリープ　1[ms]
  }

  return;
}
