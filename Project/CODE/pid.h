#ifndef __PID_H
#define __PID_H

#include "headfile.h"

typedef	struct {
    float SetSpeed;            //�����趨ֵ
    float ActualSpeed;        //����ʵ��ֵ
    float err;                //����ƫ��ֵ
    float err_last;            //������һ��ƫ��ֵ
    float Kp,Ki,Kd;            //������������֡�΢��ϵ��
    float voltage;          //�����ѹֵ������ִ�����ı�����
    float integral;            //�������ֵ
}PID;    
//pid�ṹ�嶨��



void PID_init(PID * PID);
float PID_realize(float speed, PID* PID );
float PID_Position(PID *PID, float actual, float set);





#endif


