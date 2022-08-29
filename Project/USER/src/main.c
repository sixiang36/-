/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,逐飞科技
* All rights reserved.
* 技术讨论QQ群：一群：179029047(已满)  二群：244861897
*
* 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
* 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
*
* @file				main
* @company			成都逐飞科技有限公司
* @author			逐飞科技(QQ3184284598)
* @version			查看doc内version文件 版本说明
* @Software			IAR 8.3 or MDK 5.24
* @Target core		MM32F3277
* @Taobao			https://seekfree.taobao.com/
* @date				2021-02-22
********************************************************************************************************************/

#include "headfile.h"

//删除了filter相关

// *************************** 例程说明 ***************************
// 
// 测试需要准备逐飞科技 MM32F3277 核心板一块
// 
// 调试下载需要准备逐飞科技 CMSIS-DAP 调试下载器 或 ARM 调试下载器 一个
// 
// 本例程是个空工程 用来给同学们移植使用
// 
// 打开新的工程或者工程移动了位置务必执行以下操作
// 第一步 关闭上面所有打开的文件
// 第二步 project->clean  等待下方进度条走完
// 
// *************************** 例程说明 ***************************

// **************************** 宏定义 ****************************
// **************************** 宏定义 ****************************

// **************************** 变量定义 ****************************
// **************************** 变量定义 ****************************

// **************************** 代码区域 ****************************

extern u32 par[4];

bool uart1_interrupt_flag = false;	
bool uart2_interrupt_flag = false;	
bool iflag = false;
bool runflag = true;
char IMU_BUF[250]; 
unsigned char ucRxCnt = 0;

u8 motorspeed=40;
//double KP=0.5;
double KP=10;
double KD=1;

double servo_duty;

double prepos;

double dis=20;






double predictangle1;
double predictangle2;

double predictangle3;

double pos1;
double pos2;

double pos3;

double pos6;

double pos4;//用于电机速度
float speed_kp=0.1;


	
u8 stopflag=0;
u8 disflag=0;
u8 predisflag=0;
u8 cnt;

char turn=0;
u8 i=0;


double lati5;
double longi5;





int main(void)
{
		ips200_init();
		servo_init();//舵机初始化
		gpio_init(G10, GPO, GPIO_LOW, GPO_PUSH_PULL);	//蜂鸣器初始化
		KEY_Init();
		pwm_init(MOTOR_TIM, MOTOR_PWM,motor_freq,  motor_upduty);//电机pwm初始化  
		uart_init(UART_2, 115200, UART2_TX_A02, UART2_RX_A03);//串口相关初始化，该部分使用UART2读取JY901数据
		uart_rx_irq(UART_2, ENABLE);													// 使能 UART2 的接收中断
		tim_interrupt_init(TIM_1, 10, 0x03);		
		gps_init();
		
		flash_page_read(FLASH_SECTION_127, FLASH_PAGE_1, lati1,sizelati1);
		flash_page_read(FLASH_SECTION_126, FLASH_PAGE_1, longi1, sizelongi1);
		flash_page_read(FLASH_SECTION_125, FLASH_PAGE_1, lati3,sizelati2);
		flash_page_read(FLASH_SECTION_124, FLASH_PAGE_1, longi3, sizelongi2);
		flash_page_read(FLASH_SECTION_125, FLASH_PAGE_2, lati4,sizelati3);
		flash_page_read(FLASH_SECTION_124, FLASH_PAGE_2, longi4, sizelongi3);
		flash_page_read(FLASH_SECTION_127, FLASH_PAGE_3, par,sizepar);
//	while(1)
//	{
	while(runflag)
	{
			if(stopflag==0)		
			{ 
//						motor_duty(motorspeed-speed_kp*pos4);
					if(disflag<2)
					{
							motor_duty(50);
					}
					else
					{
//						motor_duty(0);
							//motor_duty(30);
							motor_duty(par[0]);
					}
			}
			else
			{
					 motor_duty(0);   //设置其为停车
			}
			
			ips200_showstr(0,0,"motorduty:");
//			ips200_showstr(0,1,"servo_kp:");
//			ips200_showstr(0,2,"servo_kd:");
//			ips200_showstr(0,1,"gear:");
			ips200_showstr(0,1,"pointnum:");
			ips200_showstr(0,3,"index:");
			ips200_showstr(0,6,"poscnt:");
			ips200_showstr(0,7,"latitude:");
			ips200_showstr(0,8,"longitude:");
//			ips200_showstr(0,9,"gpsdir:");
			ips200_showstr(0,13,"distance:");
			ips200_showstr(0,10,"yaw:");
			ips200_showstr(0,15,"predictangle:");
			ips200_showstr(0,16,"pos:");
			ips200_showstr(0,11,"disflag:");
			ips200_showuint8(80,6,poscnt);//显示按键按下时的值，run时不会发生变化	
			ips200_showint32(80,0,par[0],5);//motorduty
//			ips200_showint32(80,1,par[1],5);
			ips200_showint32(80,1,par[2],5);
//			ips200_showint32(80,3,par[3],5);
			ips200_showuint8(80,3,changecnt+1);
			/////////////////////GPS相关调用////////////////////////////////////////////		
			if(gps_tau1201_flag)
      {
            gps_tau1201_flag = 0;
						gps_data_parse();           //开始解析数据
						ips200_showfloat(80,7,gps_tau1201.latitude,5,5);
						ips200_showfloat(80,8,gps_tau1201.longitude,5,5);
//						ips200_showfloat(80,9,gps_tau1201.direction,5,5);
						//dis=get_two_points_distance(lati5, longi5, gps_tau1201.latitude, gps_tau1201.longitude);
       }
				writeflash();
				if(disflag<60)
				{
					lati5=(double)(lati1[disflag])/100000;   //强制类型转换很重要
					longi5=(double)(longi1[disflag])/100000;
				}
				else if((disflag>59)&&(disflag<120))
				{
						lati5=(double)(lati3[disflag-60])/100000;   //强制类型转换很重要
						longi5=(double)(longi3[disflag-60])/100000;
				}
				else if((disflag>119)&&(disflag<180))
				{
						lati5=(double)(lati4[disflag-120])/100000;   //强制类型转换很重要
						longi5=(double)(longi4[disflag-120])/100000;
				}
			 	dis=get_two_points_distance(lati5, longi5, gps_tau1201.latitude, gps_tau1201.longitude);
				ips200_showfloat(80,13,dis,5,5);//显示距离
				ips200_showuint8(80,11,disflag);
					if((dis>10)) //简易距离急停测试
					{
							stopflag=1;
					}
					else 
					{		
							if(disflag<par[2])//防止最后一个点打圈
							{
									stopflag=0;
							}
							else
							{
									stopflag=1;
							}
					}
					if(dis<4)
					{
							i++;
							disflag++;
							if(disflag>par[2])
							{
									stopflag=1;
									disflag=par[2];
							}
					}
				if((disflag==par[2]))
				{
						stopflag=1;
//						pwm_duty_updata(SERVO_MOTOR_TIM, SERVO_MOTOR_PWM,3750);//舵机归位
				}				
///////////////////////////		//////////////////////中断相关////////////////////////////////////////////
			if(uart2_interrupt_flag)													// UART1 触发了接收中断
			{	
					uart2_interrupt_flag = false;	// UART1 中断标志复位
					yaw5=(double)(stcAngle.Angle[2]*0.0055);//此时yaw5的范围为-180至180
					yaw5=-yaw5;
					yaw5=yaw5-3;//手动补偿
					
					ips200_showfloat(80,10,yaw5,5,5);//显示yaw角
					pre_predictangle=predictangle1;
					judgeposition(yaw5,longi5,lati5,gps_tau1201.longitude,gps_tau1201.latitude);
					predictangle1=predictangle;
					pos1=pos;
//					ips200_showfloat(50,17,pos1,5,5);//显示偏差角度
					pos3=pos1*1+pos2*0.1;
					ips200_showfloat(50,16,pos3,5,5);//显示偏差角度
					ips200_showfloat(110,15,predictangle1,5,5);//显示预测角1  预测角由judgeposition函数得来
			}
//			change();
//			changespeed();
//			changeparam(ptr);
			changeparam(&par[1]);
			if(par[1]==1)//换挡
			{
					par[0]=60;
			}
			if(par[1]==2)//换挡
			{
					par[0]=70;
			}
			if(par[1]==3)
			{
					par[0]=90;
			}
			if(par[1]==4)
			{
					par[0]=92;
			}
			if(par[1]==5)
			{
					par[0]=95;
			}
			if(par[1]==6)
			{
					par[0]=99;
			}
			if((pos3>100)||(pos3<-100))
			{
					motor_duty(0);
			}
	}

//}
}/////////////主函数至此结束////////////////////////////////
//JY901相关/////////////////////////////////////////////////
void uart2_interrupt_handler(void)	// IMU相关*这个函数在 isr.c 的 UART1_IRQHandler 中调用
{
	uint8 Res;
	uart2_interrupt_flag = true;													// UART2 中断标志置位
	uart_getchar(UART_6, &Res);                          //对应串口2
	IMU_BUF[ucRxCnt++]=Res;
	if(IMU_BUF[0]!=0x55) //数据头不对，则重新开始寻找0x55数据头
	{
		ucRxCnt=0;
		return;
	}
	if (ucRxCnt<11) {return;}//数据不满11个，则返回
	else
	{
		switch(IMU_BUF[1])//判断数据是哪种数据，然后将其拷贝到对应的结构体中，有些数据包需要通过上位机打开对应的输出后，才能接收到这个数据包的数据
		{
			case 0x50:	memcpy(&stcTime,&IMU_BUF[2],8);break;//memcpy为编译器自带的内存拷贝函数，需引用"string.h"，将接收缓冲区的字符拷贝到数据结构体里面，从而实现数据的解析。
			case 0x51:	memcpy(&stcAcc,&IMU_BUF[2],8);break;
			case 0x52:	memcpy(&stcGyro,&IMU_BUF[2],8);break;
			case 0x53:	memcpy(&stcAngle,&IMU_BUF[2],8);break;
			case 0x54:	memcpy(&stcMag,&IMU_BUF[2],8);break;
			case 0x55:	memcpy(&stcDStatus,&IMU_BUF[2],8);break;
			case 0x56:	memcpy(&stcPress,&IMU_BUF[2],8);break;
			case 0x57:	memcpy(&stcLonLat,&IMU_BUF[2],8);break;
			case 0x58:	memcpy(&stcGPSV,&IMU_BUF[2],8);break;
			case 0x59:	memcpy(&stcQ,&IMU_BUF[2],8);break;
		}
		ucRxCnt=0;//清空缓存区
	}
	
	if(ucRxCnt>= 250)
	{
		ucRxCnt = 250;
	}	
}


void servo_pid_handler(void)
{	
		pos4=pos3;
		if(pos4<0)
		{
				pos4=-pos4;
	  } 
		if(pos3>70)
		{
				pos3=70;
		}
		if(pos3<-70)
		{ 
				pos3=-70;
		}
//		if(pos3>0)//怀疑绝对有问题
//		{
//				pos3=0;
//		}
		servo_duty=KP*pos3+KD*(pos3-prepos);
//		if(servo_duty>600)
//		{
//				servo_duty=600;
//		}
//		if(servo_duty<-600)
//		{
//				servo_duty=-600;
//		}
		
//		servo_duty=KP*sin(pos3/114.6)+KD*(pos3-prepos);
//			servo_duty=KP*pos3*pos4/8100+KD*(pos3-prepos);
//		servo_duty=KP*pos3*(4/dis)+KD*(pos3-prepos);   //用距离修改过后未经测试
			prepos=pos3;
			pwm_duty_updata(SERVO_MOTOR_TIM, SERVO_MOTOR_PWM,3850-servo_duty);//舵机根据角度偏差更新
//			if(disflag<1)
//			{
//					pwm_duty_updata(SERVO_MOTOR_TIM, SERVO_MOTOR_PWM,3780);
//			}
//			else
//			{
//				pwm_duty_updata(SERVO_MOTOR_TIM, SERVO_MOTOR_PWM,3780-servo_duty);//舵机根据角度偏差更新
//			}
}



// **************************** 代码区域 ****************************
