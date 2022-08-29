/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,��ɿƼ�
* All rights reserved.
* ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
*
* �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
* ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
*
* @file				main
* @company			�ɶ���ɿƼ����޹�˾
* @author			��ɿƼ�(QQ3184284598)
* @version			�鿴doc��version�ļ� �汾˵��
* @Software			IAR 8.3 or MDK 5.24
* @Target core		MM32F3277
* @Taobao			https://seekfree.taobao.com/
* @date				2021-02-22
********************************************************************************************************************/

#include "headfile.h"

//ɾ����filter���

// *************************** ����˵�� ***************************
// 
// ������Ҫ׼����ɿƼ� MM32F3277 ���İ�һ��
// 
// ����������Ҫ׼����ɿƼ� CMSIS-DAP ���������� �� ARM ���������� һ��
// 
// �������Ǹ��չ��� ������ͬѧ����ֲʹ��
// 
// ���µĹ��̻��߹����ƶ���λ�����ִ�����²���
// ��һ�� �ر��������д򿪵��ļ�
// �ڶ��� project->clean  �ȴ��·�����������
// 
// *************************** ����˵�� ***************************

// **************************** �궨�� ****************************
// **************************** �궨�� ****************************

// **************************** �������� ****************************
// **************************** �������� ****************************

// **************************** �������� ****************************

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

double pos4;//���ڵ���ٶ�
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
		servo_init();//�����ʼ��
		gpio_init(G10, GPO, GPIO_LOW, GPO_PUSH_PULL);	//��������ʼ��
		KEY_Init();
		pwm_init(MOTOR_TIM, MOTOR_PWM,motor_freq,  motor_upduty);//���pwm��ʼ��  
		uart_init(UART_2, 115200, UART2_TX_A02, UART2_RX_A03);//������س�ʼ�����ò���ʹ��UART2��ȡJY901����
		uart_rx_irq(UART_2, ENABLE);													// ʹ�� UART2 �Ľ����ж�
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
					 motor_duty(0);   //������Ϊͣ��
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
			ips200_showuint8(80,6,poscnt);//��ʾ��������ʱ��ֵ��runʱ���ᷢ���仯	
			ips200_showint32(80,0,par[0],5);//motorduty
//			ips200_showint32(80,1,par[1],5);
			ips200_showint32(80,1,par[2],5);
//			ips200_showint32(80,3,par[3],5);
			ips200_showuint8(80,3,changecnt+1);
			/////////////////////GPS��ص���////////////////////////////////////////////		
			if(gps_tau1201_flag)
      {
            gps_tau1201_flag = 0;
						gps_data_parse();           //��ʼ��������
						ips200_showfloat(80,7,gps_tau1201.latitude,5,5);
						ips200_showfloat(80,8,gps_tau1201.longitude,5,5);
//						ips200_showfloat(80,9,gps_tau1201.direction,5,5);
						//dis=get_two_points_distance(lati5, longi5, gps_tau1201.latitude, gps_tau1201.longitude);
       }
				writeflash();
				if(disflag<60)
				{
					lati5=(double)(lati1[disflag])/100000;   //ǿ������ת������Ҫ
					longi5=(double)(longi1[disflag])/100000;
				}
				else if((disflag>59)&&(disflag<120))
				{
						lati5=(double)(lati3[disflag-60])/100000;   //ǿ������ת������Ҫ
						longi5=(double)(longi3[disflag-60])/100000;
				}
				else if((disflag>119)&&(disflag<180))
				{
						lati5=(double)(lati4[disflag-120])/100000;   //ǿ������ת������Ҫ
						longi5=(double)(longi4[disflag-120])/100000;
				}
			 	dis=get_two_points_distance(lati5, longi5, gps_tau1201.latitude, gps_tau1201.longitude);
				ips200_showfloat(80,13,dis,5,5);//��ʾ����
				ips200_showuint8(80,11,disflag);
					if((dis>10)) //���׾��뼱ͣ����
					{
							stopflag=1;
					}
					else 
					{		
							if(disflag<par[2])//��ֹ���һ�����Ȧ
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
//						pwm_duty_updata(SERVO_MOTOR_TIM, SERVO_MOTOR_PWM,3750);//�����λ
				}				
///////////////////////////		//////////////////////�ж����////////////////////////////////////////////
			if(uart2_interrupt_flag)													// UART1 �����˽����ж�
			{	
					uart2_interrupt_flag = false;	// UART1 �жϱ�־��λ
					yaw5=(double)(stcAngle.Angle[2]*0.0055);//��ʱyaw5�ķ�ΧΪ-180��180
					yaw5=-yaw5;
					yaw5=yaw5-3;//�ֶ�����
					
					ips200_showfloat(80,10,yaw5,5,5);//��ʾyaw��
					pre_predictangle=predictangle1;
					judgeposition(yaw5,longi5,lati5,gps_tau1201.longitude,gps_tau1201.latitude);
					predictangle1=predictangle;
					pos1=pos;
//					ips200_showfloat(50,17,pos1,5,5);//��ʾƫ��Ƕ�
					pos3=pos1*1+pos2*0.1;
					ips200_showfloat(50,16,pos3,5,5);//��ʾƫ��Ƕ�
					ips200_showfloat(110,15,predictangle1,5,5);//��ʾԤ���1  Ԥ�����judgeposition��������
			}
//			change();
//			changespeed();
//			changeparam(ptr);
			changeparam(&par[1]);
			if(par[1]==1)//����
			{
					par[0]=60;
			}
			if(par[1]==2)//����
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
}/////////////���������˽���////////////////////////////////
//JY901���/////////////////////////////////////////////////
void uart2_interrupt_handler(void)	// IMU���*��������� isr.c �� UART1_IRQHandler �е���
{
	uint8 Res;
	uart2_interrupt_flag = true;													// UART2 �жϱ�־��λ
	uart_getchar(UART_6, &Res);                          //��Ӧ����2
	IMU_BUF[ucRxCnt++]=Res;
	if(IMU_BUF[0]!=0x55) //����ͷ���ԣ������¿�ʼѰ��0x55����ͷ
	{
		ucRxCnt=0;
		return;
	}
	if (ucRxCnt<11) {return;}//���ݲ���11�����򷵻�
	else
	{
		switch(IMU_BUF[1])//�ж��������������ݣ�Ȼ���俽������Ӧ�Ľṹ���У���Щ���ݰ���Ҫͨ����λ���򿪶�Ӧ������󣬲��ܽ��յ�������ݰ�������
		{
			case 0x50:	memcpy(&stcTime,&IMU_BUF[2],8);break;//memcpyΪ�������Դ����ڴ濽��������������"string.h"�������ջ��������ַ����������ݽṹ�����棬�Ӷ�ʵ�����ݵĽ�����
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
		ucRxCnt=0;//��ջ�����
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
//		if(pos3>0)//���ɾ���������
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
//		servo_duty=KP*pos3*(4/dis)+KD*(pos3-prepos);   //�þ����޸Ĺ���δ������
			prepos=pos3;
			pwm_duty_updata(SERVO_MOTOR_TIM, SERVO_MOTOR_PWM,3850-servo_duty);//������ݽǶ�ƫ�����
//			if(disflag<1)
//			{
//					pwm_duty_updata(SERVO_MOTOR_TIM, SERVO_MOTOR_PWM,3780);
//			}
//			else
//			{
//				pwm_duty_updata(SERVO_MOTOR_TIM, SERVO_MOTOR_PWM,3780-servo_duty);//������ݽǶ�ƫ�����
//			}
}



// **************************** �������� ****************************
