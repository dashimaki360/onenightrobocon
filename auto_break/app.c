/*
 * TOPPERS/EV3　サンプル　「壁に衝突しない」
 * 動作説明　　直進して、壁が一定距離以下に近づくと止まる
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
  const int stop_dist = 10; //停止距離[cm]
  uint32_t power = 50;      //モーターパワー(-100 ~ +100)
  int steer = 0;            //操舵角(-100 ~ +100)
  int dist = 0;             //計測距離[cm]

  while(1){
    //距離情報の取得
    dist = ev3_ultrasonic_sensor_get_distance(u_sonic_sensor);
    //距離取得エラーの場合無視する
    if(dist == 0) continue;

    //壁が近いか判断する
    if(stop_dist > dist){
      //モーターのパワーを0に
      power = 0;
    }
    //表示
    char msg[256]= {0};
    sprintf(msg, "distance_val %03d", dist);
    ev3_lcd_draw_string(msg,0,20);

    //モーターパワー更新
    ev3_motor_steer(left_motor, right_motor, power, steer);

    //スリープ　10[ms]
    tslp_tsk(10); 
  }

  return;
}
