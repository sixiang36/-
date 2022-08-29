#include "servo.h"

/*waaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
*  �������ƣ�servo_init(void)
*  ����˵����         
*  ����˵����servo motor init
*  �������أ���
*  �޸�ʱ�䣺2022.1.9
*  ��    ע��   
*  ��    �ߣ�Mr.wave 
*Sample usage:
vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvve*/
void servo_init(void)
{
	pwm_init(SERVO_MOTOR_TIM, SERVO_MOTOR_PWM, SERVO_MOTOR_FREQ, SERVO_MOTOR_DUTY );	
	
}


/*waaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
*  �������ƣ�servo_updata(float delta_angle)
*  ����˵����         
*  ����˵����servo_updata(delta_angle)
*  �������أ���
*  �޸�ʱ�䣺2022.1.10
*  ��    ע��   
*  ��    �ߣ�Mr.wave 
*Sample usage:
vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvve*/
void servo_updata(float alpha_angle)
{
//	if( delta_angle )
//	{
//	
//	}
//	else
//	{	
	float delta_angle=alpha_angle+90.0;
	float err_angle_duty;
	err_angle_duty=PWM_DUTY_MAX/(1000/SERVO_MOTOR_FREQ)*(1+delta_angle/180.0);
	pwm_duty_updata(SERVO_MOTOR_TIM, SERVO_MOTOR_PWM,err_angle_duty);
//	}
}









//void servo_updata(float delta_angle)
//{

//	float err_angle_duty;
//	err_angle_duty=PWM_DUTY_MAX/(1000/SERVO_MOTOR_FREQ)*(1+delta_angle/180.0);
//	pwm_duty_updata(SERVO_MOTOR_TIM, SERVO_MOTOR_PWM,err_angle_duty);

//}

