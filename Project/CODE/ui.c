#include "ui.h"
 
unsigned int nowIndex = 0;

extern bool runflag;
extern u8 motorspeed;

extern u32 par[4];


u32  lati1[60];
u32  longi1[60];

u32  lati3[60];
u32  longi3[60];

u32  lati4[60];
u32  longi4[60];



u8 laticnt;
u8 longicnt;

u8 poscnt;


u8 changecnt=0;

u8 key;


u32 par[4]={40,10,1,100};




void writeflash()  //写flash时可能不能连续写
{
		u8 keyflag=0;
		key=KEY_Scan();
		if(key==6)//确定  按下一次大按键按键蜂鸣器响一次
		{
				keyflag=1;
				if(laticnt<60)
				{
					lati1[laticnt]=(gps_tau1201.latitude)*100000;
					longi1[longicnt]=(gps_tau1201.longitude)*100000;
				}
				else if((laticnt>59)&&(laticnt<120))
				{
						lati3[laticnt-60]=(gps_tau1201.latitude)*100000;
						longi3[longicnt-60]=(gps_tau1201.longitude)*100000;
				}
				else if((laticnt>119)&&(laticnt<180))
				{
						lati4[laticnt-120]=(gps_tau1201.latitude)*100000;
						longi4[longicnt-120]=(gps_tau1201.longitude)*100000;
				}
				laticnt++;
				longicnt++;
				poscnt=laticnt;
//				if((laticnt>132)||(longicnt>132))//也许可以不要
//				{
//						laticnt=132;
//						longicnt=132;
//				}
				gpio_set(G10, 1);     //设置其为高电平,蜂鸣器响
				systick_delay_ms(10);
				gpio_set(G10, 0); 
//				poscnt=poscnt-1; //删去之后下面的值+1
				if(poscnt==par[2])//pointnum
				{
						flash_page_program(FLASH_SECTION_127, FLASH_PAGE_1, lati1, sizelati1);//写入
						flash_page_program(FLASH_SECTION_126, FLASH_PAGE_1, longi1, sizelongi1);//写入
						flash_page_program(FLASH_SECTION_125, FLASH_PAGE_1, lati3, sizelati2);//写入
						flash_page_program(FLASH_SECTION_124, FLASH_PAGE_1, longi3, sizelongi2);//写入
						flash_page_program(FLASH_SECTION_125, FLASH_PAGE_2, lati4, sizelati3);//写入
						flash_page_program(FLASH_SECTION_124, FLASH_PAGE_2, longi4, sizelongi3);//写入
						flash_page_program(FLASH_SECTION_127, FLASH_PAGE_3, par,sizepar);//写入
				}
		}

}

void change()//切换界面
{
	
		key=KEY_Scan();
		if(key==4)//下按
		{
				runflag=!runflag;
				ips200_clear(RED);
		}
}


void changespeed()
{
		key=KEY_Scan();
		if(key==3)//右按
		{
				motorspeed=motorspeed+5;
		}
		else if(key==1)//左按
		{
				motorspeed=motorspeed-5;
		}
}

void changeparam(u32 *a)
{
		
		key=KEY_Scan();
		if(key==2)//上按
		{
				changecnt--;
				gpio_set(G10, 1);     //设置其为高电平,蜂鸣器响
				systick_delay_ms(10);
				gpio_set(G10, 0); 
		}
		if(key==5)//下按
		{
				changecnt++;
				gpio_set(G10, 1);     //设置其为高电平,蜂鸣器响
				systick_delay_ms(10);
				gpio_set(G10, 0); 
		}
		if(key==3)//右按
		{
				*(a+changecnt)=*(a+changecnt)+1;
			
		}
		if(key==1)//左按
		{
				*(a+changecnt)=*(a+changecnt)-1;
				
		}
}
