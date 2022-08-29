#include "servo.h"

/*waaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
*  函数名称：servo_init(void)
*  功能说明：         
*  参数说明：servo motor init
*  函数返回：无
*  修改时间：2022.1.9
*  备    注：   
*  作    者：Mr.wave 
*Sample usage:
vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvve*/
void servo_init(void)
{
	pwm_init(SERVO_MOTOR_TIM, SERVO_MOTOR_PWM, SERVO_MOTOR_FREQ, SERVO_MOTOR_DUTY );	
	
}


/*waaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
*  函数名称：servo_updata(float delta_angle)
*  功能说明：         
*  参数说明：servo_updata(delta_angle)
*  函数返回：无
*  修改时间：2022.1.10
*  备    注：   
*  作    者：Mr.wave 
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

