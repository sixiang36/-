#include "key.h"

void KEY_Init(void)//五项按键初始化
{
//    gpio_init(B0,GPI,GPIO_HIGH,GPI_PULL_UP);
//    gpio_init(B2,GPI,GPIO_HIGH,GPI_PULL_UP);
//    gpio_init(B1,GPI,GPIO_HIGH,GPI_PULL_UP);
//    gpio_init(F13,GPI,GPIO_HIGH,GPI_PULL_UP);
//    gpio_init(F11,GPI,GPIO_HIGH,GPI_PULL_UP);
	  gpio_init(B5,GPI,GPIO_HIGH,GPI_PULL_UP);
    gpio_init(B6,GPI,GPIO_HIGH,GPI_PULL_UP);
    gpio_init(B7,GPI,GPIO_HIGH,GPI_PULL_UP);
    gpio_init(B8,GPI,GPIO_HIGH,GPI_PULL_UP);
    gpio_init(B9,GPI,GPIO_HIGH,GPI_PULL_UP);
		gpio_init(G9,GPI,GPIO_HIGH,GPI_PULL_UP);//新大按键
}



u8 KEY_Scan(void)
{	 
	u8 key=0;
	if(KEY1==0||KEY2==0||KEY3==0||KEY4==0||KEY5==0||KEY6==0)
	{
		systick_delay_ms(100);//去抖动 
		if(KEY1==0)key=1;
		else if(KEY2==0)key=2;
		else if(KEY3==0)key=3;
		else if(KEY4==0)key=4;
		else if(KEY5==0)key=5;
		else if(KEY6==0)key=6;
		systick_delay_us(50000);
	}
 	return key;// 无按键按下
}
