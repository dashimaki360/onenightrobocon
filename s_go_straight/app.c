/**
 * TOPPERS/EV3　サンプル　「真っすぐ進んで止まる」.
 * 動作説明　　一定量直進して、止まる
 */

#include "ev3api.h"
#include "app.h"

/**
 * ポートの接続対応
 * Touch sensor: Port 2 //今回は未使用
 * Color sensor: Port 3 //今回は未使用
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


  const int rot_deg = 360*10; //回転角度　20回転
  uint32_t power = 50;  //モーターパワー
  bool_t is_block_motor = true;  //回転終了後モータをロックする
  ev3_motor_reset_counts(left_motor);//モーターの回転角リセット

  while(1){

    //指定量モーターが回転したか判定
    if( rot_deg < ev3_motor_get_counts(left_motor) ){
      power = 0;
    }
    ev3_motor_set_power(left_motor, power);//左モータ回転
    ev3_motor_set_power(right_motor, power);//右モータ回転

    tslp_tsk(1); //スリープ　1[ms]
  }

  return;
}
