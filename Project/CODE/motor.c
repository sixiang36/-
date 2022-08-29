#include "motor.h"


/*waaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
*  �������ƣ�motor_init(void)
*  ����˵���� unlock bldc_motor       
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2022.1.9
*  ��    ע��   
*  ��    �ߣ�Mr.wave 
*Sample usage:motor_init(void)
vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvve*/
void motor_init(void)//�����ں�ӯ���
{
		pwm_init (MOTOR_TIM, MOTOR_PWM,motor_freq,  motor_upduty);//�������pwm  Ƶ��400hz  ����������Ҫ��72%ռ�ձ�������73%
		systick_delay_ms (500);
		pwm_duty_updata( MOTOR_TIM, MOTOR_PWM,motor_onduty);//�������63%  ���ڷŴ��·��λȡ��������ȡ��ֵ  ��22.1.7.  15��18ʵ��ɹ�
		systick_delay_ms (500);

}




/*waaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
*  �������ƣ�motor_duty(float motor_loaduty)
*  ����˵���� motor input duty ; in from  62.7  to  80.0     
*  ����˵����motor_loaduty:duty percent
*  �������أ���
*  �޸�ʱ�䣺2022.1.10
*  ��    ע��   
*  ��    �ߣ�Mr.wave 
*Sample usage:   motor_duty(75.0);
vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvve*/
void motor_duty(float motor_loaduty)
{
	float motor_loading;
	//motor_loading=(100.0-motor_loaduty)*500;
		motor_loading=(motor_loaduty)*500;
	pwm_duty_updata( MOTOR_TIM, MOTOR_PWM,(unsigned long int)motor_loading);
	
}
	
