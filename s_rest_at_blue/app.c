/**
 * TOPPERS/EV3　サンプル　「青いところで止まる」.
 * 動作説明　　直進して、青いところで止まる
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


  uint32_t power = 20;  //モーターパワー
  int steer = 0;

  //直進
  ev3_motor_steer(left_motor, right_motor, power, steer);


  while(1){
    //色情報の取得

    //床が青いか判断する
    if(BLUE == color){
      //モーターの停止
      ev3_motor_steer(left_motor, right_motor, 0, steer);
    }

    tslp_tsk(1); //スリープ　1[ms]
  }

  return;
}
