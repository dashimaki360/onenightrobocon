#ifndef MAIN_COOKIE_MONSTER
#define MAIN_COOKIE_MONSTER
/**
 * ポートの接続対応
 * Touch sensor: Port 2
 * Color sensor: Port 3 //ライントレース用
 * USonic sensor: Port 4
 * Left  motor:  Port B
 * Right motor:  Port C
 */
const int touch_sensor = EV3_PORT_2;
const int line_sensor = EV3_PORT_3;
const int u_sonic_sensor = EV3_PORT_4;
const int left_motor = EV3_PORT_B;
const int right_motor = EV3_PORT_C;

void main_task(intptr_t exinf);
#endif // MAIN_COOKIE_MONSTER
