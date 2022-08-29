#ifndef __UI_H
#define __UI_H

#include "headfile.h"




#define sizelati1 sizeof(lati1)		//数组长度
#define sizelongi1 sizeof(longi1)		//数组长度

#define sizelati2 sizeof(lati3)		//数组长度
#define sizelongi2 sizeof(longi3)		//数组长度


#define sizelati3 sizeof(lati4)		//数组长度
#define sizelongi3 sizeof(longi4)		//数组长度
	
#define sizepar sizeof(par)	


extern u32  lati1[60];
extern u32  longi1[60];

extern u32  lati3[60];
extern u32  longi3[60];

extern u32  lati4[60];
extern u32  longi4[60];



extern u8 laticnt;
extern u8 longicnt;
extern u8 poscnt;

extern u8 changecnt;



//extern u8 keyflag;




void writeflash(void);
void change(void);

void changespeed(void);
void changeparam(u32 *a);

#endif

