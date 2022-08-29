#ifndef __CONTROL_H
#define __CONTROL_H

#include "headfile.h"






extern char dir;



extern float pos;

extern double predictangle;
extern double pre_predictangle;


extern double yaw5;//JY901测出来的值





double judgeposition(double a,double b,double c,double d,double e);
float anglecalculate(float a,float b,float c,float d);







double getdistance(double a,double b ,double c,double d);


double getdistance2(double *a,double *b,double *c,double *d);




#endif

