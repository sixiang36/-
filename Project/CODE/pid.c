#include "pid.h"


void PID_init(PID * PID)
	{
	
    PID->SetSpeed=0.0;
    PID->ActualSpeed=0.0;
    PID->err=0.0;
    PID->err_last=0.0;
    PID->voltage=0.0;
    PID->integral=0.0;
		PID->Kp=0.2;
    PID->Ki=0.015;
    PID->Kd=0.2;
  
}   


/*waaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
*  �������ƣ�float PID_realize(float speed, pid * PID )
*  ����˵���� ����ʽpid        
*  ����˵����speed �����ٶ�   PID ����pid�ṹ��
*  �������أ�
*  �޸�ʱ�䣺2022.1.9
*  ��    ע��   
*  ��    �ߣ�Mr.wave (ԭ���ߣ�)
*Sample usage:float PID_realize(expect_speed, &pid_motor )
vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvve*/

float PID_realize(float speed, PID* PID )
{
    PID->SetSpeed=speed;
    PID->err= PID->SetSpeed- PID->ActualSpeed;
    PID->integral+= PID->err;
    PID->voltage= PID->Kp* PID->err+ PID->Ki* PID->integral+ PID->Kd*( PID->err- PID->err_last);
    PID->err_last= PID->err;
    PID->ActualSpeed= PID->voltage*1.0;
    return  PID->ActualSpeed;
}


/*waaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
*  �������ƣ�float PID_Position(pid *PID, float actual, float set)
*  ����˵����  λ��ʽpid       
*  ����˵����actual ��ǰֵ  set ����ֵ
*  �������أ�
*  �޸�ʱ�䣺2022.1.9
*  ��    ע��   
*  ��    �ߣ�Mr.wave (ԭ���ߣ�xinnz)
*Sample usage:PID_Position(&pid_motor,  actual, set)
vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvve*/
float PID_Position(PID *PID, float actual, float set)
{
    float iError;   //>��ǰ���
    float Position; //>���ó���ʵ�����

    /*���㵱ǰ���*/
    iError = set - actual;

    /* �ۻ���� - �˳�ģλ��ʽ��ʹ��PD */
    //pid->integrator += pid->kI * iError;

    /* ����޷� */
    //pid->integrator = PID_Limiter_float(pid->integrator, (float)(0 - pid->integral_limit), (float)(pid->integral_limit));

    /* �����ļ��� */
    Position = (float)(PID->Kp * iError +PID->Kd * (iError - PID->err_last));
    //Position = (int32)(pid->kP * iError + pid->integrator + pid->kD * (iError - pid->last_error));

    /* �����ϴ���� */
    PID->err_last = iError;

    return Position;
}

