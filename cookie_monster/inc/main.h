#ifndef MAIN_COOKIE_MONSTER
#define MAIN_COOKIE_MONSTER
/**
 * �|�[�g�̐ڑ��Ή�
 * Color sensor: Port 3
 * Touch sensor: Port 2
 * Line sensor: Port 4 //���C���g���[�X�p
 * USonic sensor: Port 1
 * Left  motor:  Port B
 * Right motor:  Port C
 */

static const int color_sensor = EV3_PORT_3;
static const int touch_sensor = EV3_PORT_2;
static const int line_sensor = EV3_PORT_4;
static const int u_sonic_sensor = EV3_PORT_1;
static const int medium_motor = EV3_PORT_A;
static const int left_motor = EV3_PORT_B;
static const int right_motor = EV3_PORT_C;

void main_task(intptr_t exinf);
#endif // MAIN_COOKIE_MONSTER
