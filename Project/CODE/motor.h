#ifndef __MOTOR_H
#define __MOTOR_H

#include "headfile.h"


#define  motor_freq  2000
#define  motor_upduty  10000
#define  MOTOR_TIM  TIM_2
//#define  MOTOR_PWM  TIM_2_CH2_A01
#define  MOTOR_PWM TIM_2_CH2_B03	//新主板电机接口
#define  duty_min  15000
#define  motor_onduty 18500

void motor_init(void);
void motor_duty(float motor_loaduty);



#endif

