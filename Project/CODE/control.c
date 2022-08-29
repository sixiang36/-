#include "control.h"


float pos;

double pre_predictangle;

double yaw5;//JY901测出来的值

float angle;
double predictangle;


char  dir;




//a为yaw，b为longi[i]，c为lati[i]，d为longitude，e为latitude
double judgeposition(double a,double b,double c,double d,double e)//a为形参，一般为yaw值
{
//	pre_predictangle=predictangle;
	predictangle= get_two_points_azimuth(e, d, c, b);
		//完成此操作后pos范围为-180至180///////////////////////////
	if((-180<a-predictangle)&&(a-predictangle<180))
		pos=-predictangle+a;
	if(a-predictangle<-180)
		pos=-predictangle+a+360;       //此时0至180
	if(a-predictangle>180)
		pos=-predictangle+a-360;     //此时pos为-180至0
	
	

	

	

		

	
		return pos;
		
		
		
//		if(predictangle<0)//yaw经过转换后一定为正数，转换函数在上
//		{
//				pos=a-predictangle;//误差值的计算
//				if(pos>360)
//				{
//						pos=pos-360;
//				}
//		}
//		if(predictangle>0)//算出来的pos一定为正数,且pos值与舵机打角值有关
//		{
//				if(a<predictangle)
//				{
//						pos=predictangle-a;
//				}
//				if(a>predictangle)
//				{
//						pos=a-predictangle;
//				}
//		}
//		servo_updata(pos);
	
		
}

float anglecalculate(float a,float b,float c,float d)//角度计算
{
//		predictangle=FastAtan2((c-a), (d-b));
		predictangle=atan2((c-a),(d-b));
		predictangle=predictangle*57.3248;//计算出来的范围为-45到45
		predictangle=predictangle/4;    //限制其范围

		if(predictangle>0)
		{
				predictangle=45-predictangle;
		}
		else
		{
					predictangle=-45-predictangle;
		}
		return predictangle;
}

double getdistance(double a,double b ,double c,double d)
{
		double distance;
		distance=sqrt((c-a)*(c-a)+(d-b)*(d-b));
		return distance;
}


double getdistance2(double *a,double *b,double *c,double *d)
{
		double  distance;
		distance=sqrt((*c-*a)*(*c-*a)+(*d-*b)*(*d-*b));
		return  distance;
}

