/**
 * TOPPERS/EV3�@�T���v���@�u�^�������i��Ŏ~�܂�v.
 * ��������@�@���ʒ��i���āA�~�܂�
 */

#include "ev3api.h"
#include "app.h"

/**
 * �|�[�g�̐ڑ��Ή�
 * Touch sensor: Port 2 //����͖��g�p
 * Color sensor: Port 3 //����͖��g�p
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


  const int rot_deg = 360*10; //��]�p�x�@20��]
  uint32_t power = 50;  //���[�^�[�p���[
  bool_t is_block_motor = true;  //��]�I���ヂ�[�^�����b�N����
  ev3_motor_reset_counts(left_motor);//���[�^�[�̉�]�p���Z�b�g

  while(1){

    //�w��ʃ��[�^�[����]����������
    if( rot_deg < ev3_motor_get_counts(left_motor) ){
      power = 0;
    }
    ev3_motor_set_power(left_motor, power);//�����[�^��]
    ev3_motor_set_power(right_motor, power);//�E���[�^��]

    tslp_tsk(1); //�X���[�v�@1[ms]
  }

  return;
}
