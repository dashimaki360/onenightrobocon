/**
 * TOPPERS/EV3　サンプル　「赤信号で止まる」.
 * 動作説明　　直進して、床が赤いところで止まる
 */

#include "ev3api.h"
#include "app.h"

/**
 * ポートの接続対応
 * Touch sensor: Port 2
 * Color sensor: Port 3
 * USonic sensor: Port 4
 * Left  motor:  Port B
 * Right motor:  Port C
 */
const int touch_sensor = EV3_PORT_2;
const int color_sensor = EV3_PORT_3;
const int u_sonic_sensor = EV3_PORT_4;
const int left_motor = EV3_PORT_B;
const int right_motor = EV3_PORT_C;

//メインタスク
void main_task(intptr_t unused) {

  //モーターポートを設定 
  ev3_motor_config(left_motor, LARGE_MOTOR);
  ev3_motor_config(right_motor, LARGE_MOTOR);

  //センサーポートを設定
  ev3_sensor_config(touch_sensor, TOUCH_SENSOR);
  ev3_sensor_config(color_sensor, COLOR_SENSOR);
  ev3_sensor_config(u_sonic_sensor, ULTRASONIC_SENSOR);

  //変数宣言
  const int stop_color = COLOR_RED;  //停止する色、今回は「赤」
  uint32_t power = 20;               //モーターパワー(-100 ~ +100)
  int steer = 0;                     //操舵角(-100 ~ +100)
  int color = COLOR_NONE;            //計測色[cm]

  while(1){
    //色情報の取得
    color = ev3_color_sensor_get_color(color_sensor);

    //床が赤いか判断する
    if(stop_color == color){
      //モーターのパワーを0に
      power = 0;
    }

    //モーターパワー更新
    ev3_motor_steer(left_motor, right_motor, power, steer);

    //スリープ　10[ms]
    tslp_tsk(10); 
  }

  return;
}

