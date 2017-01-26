/**
 * TOPPERS/EV3�@�T���v���@�u�������ɉ����Đi�ށv.
 * ��������@�@�������ɉ����Đi�ށB�~�܂邱�Ƃ͂Ȃ��B
 */

#include "ev3api.h"
#include "app.h"

/**
 * �|�[�g�̐ڑ��Ή�
 * Touch sensor: Port 2 //����͖��g�p
 * Color sensor: Port 3
 * USonic sensor: Port 4 //����͖��g�p
 * Left  motor:  Port B
 * Right motor:  Port C
 */
const int touch_sensor = EV3_PORT_2;
const int color_sensor = EV3_PORT_3;
const int u_sonic_sensor = EV3_PORT_4;
const int left_motor = EV3_PORT_B;
const int right_motor = EV3_PORT_C;

void main_task(intptr_t unused) {
  //���[�^�[�|�[�g��ݒ� 
  ev3_motor_config(left_motor, LARGE_MOTOR);
  ev3_motor_config(right_motor, LARGE_MOTOR);

  //�Z���T�[�|�[�g��ݒ�
  ev3_sensor_config(touch_sensor, TOUCH_SENSOR);
  ev3_sensor_config(color_sensor, COLOR_SENSOR);
  ev3_sensor_config(u_sonic_sensor, ULTRASONIC_SENSOR);


  const int mid_point = 50; //���ƍ���臒l
  const int power = 50;  //���[�^�[�p���[j
  int steer = 0;  //�n���h�������


  while(1){
    //���邳�擾
    int reflect_val = ev3_color_sensor_get_reflect(color_sensor);

    //�n���h������ʌ���
    if(reflect_val > mid_point){ //����
      steer = 30;
    }else{  //����
      steer = -30;
    }

    //���[�^����ʂ��Z�b�g
    ev3_motor_steer(left_motor, right_motor, power, steer);

    //���邳�ƃn���h������ʂ�\��
    char msg[256]= {0};
    sprintf(msg, "reflect_val:%03d steer:%03d", reflect_val, steer);
    ev3_lcd_draw_string(msg,0,20);

    tslp_tsk(1); //�X���[�v�@1[ms]
  }

  return;
}
