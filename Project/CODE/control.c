#include "control.h"


float pos;

double pre_predictangle;

double yaw5;//JY901�������ֵ

float angle;
double predictangle;


char  dir;




//aΪyaw��bΪlongi[i]��cΪlati[i]��dΪlongitude��eΪlatitude
double judgeposition(double a,double b,double c,double d,double e)//aΪ�βΣ�һ��Ϊyawֵ
{
//	pre_predictangle=predictangle;
	predictangle= get_two_points_azimuth(e, d, c, b);
		//��ɴ˲�����pos��ΧΪ-180��180///////////////////////////
	if((-180<a-predictangle)&&(a-predictangle<180))
		pos=-predictangle+a;
	if(a-predictangle<-180)
		pos=-predictangle+a+360;       //��ʱ0��180
	if(a-predictangle>180)
		pos=-predictangle+a-360;     //��ʱposΪ-180��0
	
	

	

	

		

	
		return pos;
		
		
		
//		if(predictangle<0)//yaw����ת����һ��Ϊ������ת����������
//		{
//				pos=a-predictangle;//���ֵ�ļ���
//				if(pos>360)
//				{
//						pos=pos-360;
//				}
//		}
//		if(predictangle>0)//�������posһ��Ϊ����,��posֵ�������ֵ�й�
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

float anglecalculate(float a,float b,float c,float d)//�Ƕȼ���
{
//		predictangle=FastAtan2((c-a), (d-b));
		predictangle=atan2((c-a),(d-b));
		predictangle=predictangle*57.3248;//��������ķ�ΧΪ-45��45
		predictangle=predictangle/4;    //�����䷶Χ

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

