#ifndef __KEY_H
#define __KEY_H

#include "headfile.h"


#define KEY1_PRES 	1	//KEY0����
#define KEY2_PRES	  2	//KEY1��
#define KEY3_PRES   3	//KEY2����
#define KEY4_PRES   4 //KEY2����
#define KEY5_PRES   5	//KEY2����
#define KEY6_PRES   6	//KEY2����


#define KEY1 gpio_get(B5)//��
#define KEY2 gpio_get(B6)//��
#define KEY3 gpio_get(B7)//��
#define KEY4 gpio_get(B8)//ȷ��
#define KEY5 gpio_get(B9)//��
#define KEY6 gpio_get(G9)//�󰴼�
void KEY_Init(void);
//u8 KEY_Scan(u8 mode);
u8 KEY_Scan(void);

#endif

