#ifndef __SERVO_H
#define __SERVO_H

#include "headfile.h"

//#define SERVO_MOTOR_TIM				TIM_8									// 定义主板上舵机对应TIM
//#define SERVO_MOTOR_PWM				TIM_8_CH3_C08								// 定义主板上舵机对应引脚


#define SERVO_MOTOR_PWM				TIM_3_CH1_B04								// 定义新主板上舵机对应引脚TIM_3_CH1_B04	
#define SERVO_MOTOR_TIM				TIM_3								// 定义主板上舵机对应TIM
#define SERVO_MOTOR_FREQ			50											// 定义主板上舵机频率  请务必注意范围 50-300
#define SERVO_MOTOR_DUTY      3850


#define SERVO_MOTOR_L_MAX			45												// 定义主板上舵机活动范围 角度
#define SERVO_MOTOR_R_MAX			135											// 定义主板上舵机活动范围 角度


void servo_init(void);
void servo_updata(float alpha_angle);

//void servo_updata(float delta_angle);


#endif

