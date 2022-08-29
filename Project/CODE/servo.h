#ifndef __SERVO_H
#define __SERVO_H

#include "headfile.h"

//#define SERVO_MOTOR_TIM				TIM_8									// ���������϶����ӦTIM
//#define SERVO_MOTOR_PWM				TIM_8_CH3_C08								// ���������϶����Ӧ����


#define SERVO_MOTOR_PWM				TIM_3_CH1_B04								// �����������϶����Ӧ����TIM_3_CH1_B04	
#define SERVO_MOTOR_TIM				TIM_3								// ���������϶����ӦTIM
#define SERVO_MOTOR_FREQ			50											// ���������϶��Ƶ��  �����ע�ⷶΧ 50-300
#define SERVO_MOTOR_DUTY      3850


#define SERVO_MOTOR_L_MAX			45												// ���������϶�����Χ �Ƕ�
#define SERVO_MOTOR_R_MAX			135											// ���������϶�����Χ �Ƕ�


void servo_init(void);
void servo_updata(float alpha_angle);

//void servo_updata(float delta_angle);


#endif

