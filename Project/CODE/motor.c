#include "motor.h"


/*waaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
*  函数名称：motor_init(void)
*  功能说明： unlock bldc_motor       
*  参数说明：
*  函数返回：无
*  修改时间：2022.1.9
*  备    注：   
*  作    者：Mr.wave 
*Sample usage:motor_init(void)
vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvve*/
void motor_init(void)//适用于好盈电调
{
		pwm_init (MOTOR_TIM, MOTOR_PWM,motor_freq,  motor_upduty);//解锁电机pwm  频率400hz  解锁过程需要从72%占空比上升到73%
		systick_delay_ms (500);
		pwm_duty_updata( MOTOR_TIM, MOTOR_PWM,motor_onduty);//电机解锁63%  由于放大电路相位取反，这里取反值  于22.1.7.  15：18实验成功
		systick_delay_ms (500);

}




/*waaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
*  函数名称：motor_duty(float motor_loaduty)
*  功能说明： motor input duty ; in from  62.7  to  80.0     
*  参数说明：motor_loaduty:duty percent
*  函数返回：无
*  修改时间：2022.1.10
*  备    注：   
*  作    者：Mr.wave 
*Sample usage:   motor_duty(75.0);
vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvve*/
void motor_duty(float motor_loaduty)
{
	float motor_loading;
	//motor_loading=(100.0-motor_loaduty)*500;
		motor_loading=(motor_loaduty)*500;
	pwm_duty_updata( MOTOR_TIM, MOTOR_PWM,(unsigned long int)motor_loading);
	
}
	
