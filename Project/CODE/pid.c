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
*  函数名称：float PID_realize(float speed, pid * PID )
*  功能说明： 增量式pid        
*  参数说明：speed 期望速度   PID 传入pid结构体
*  函数返回：
*  修改时间：2022.1.9
*  备    注：   
*  作    者：Mr.wave (原作者：)
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
*  函数名称：float PID_Position(pid *PID, float actual, float set)
*  功能说明：  位置式pid       
*  参数说明：actual 当前值  set 期望值
*  函数返回：
*  修改时间：2022.1.9
*  备    注：   
*  作    者：Mr.wave (原作者：xinnz)
*Sample usage:PID_Position(&pid_motor,  actual, set)
vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvve*/
float PID_Position(PID *PID, float actual, float set)
{
    float iError;   //>当前误差
    float Position; //>最后得出的实际输出

    /*计算当前误差*/
    iError = set - actual;

    /* 累积误差 - 此车模位置式仅使用PD */
    //pid->integrator += pid->kI * iError;

    /* 误差限幅 */
    //pid->integrator = PID_Limiter_float(pid->integrator, (float)(0 - pid->integral_limit), (float)(pid->integral_limit));

    /* 增量的计算 */
    Position = (float)(PID->Kp * iError +PID->Kd * (iError - PID->err_last));
    //Position = (int32)(pid->kP * iError + pid->integrator + pid->kD * (iError - pid->last_error));

    /* 更新上次误差 */
    PID->err_last = iError;

    return Position;
}

