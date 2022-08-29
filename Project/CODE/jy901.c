#include "jy901.h"



struct STime		stcTime;
struct SAcc 		stcAcc;
struct SGyro 		stcGyro;
struct SAngle 	stcAngle;
struct SMag 		stcMag;
struct SDStatus stcDStatus;
struct SPress 	stcPress;
struct SLonLat 	stcLonLat;
struct SGPSV 		stcGPSV;
struct SQ       stcQ;


////CopeSerialData为串口1中断调用函数，串口每收到一个数据，调用一次这个函数。
//void CopeSerial1Data(void)
//{
//	
//	uint8 res;
//	uart_getchar(UART_1, &res);//获取数据
//	static unsigned char ucRxBuffer[250];
//	static unsigned char ucRxCnt = 0;	
//	
//	
//	
////	LED_REVERSE();					//接收到数据，LED灯闪烁一下
//	ucRxBuffer[ucRxCnt++]=res;	//将收到的数据存入缓冲区中
//	if (ucRxBuffer[0]!=0x55) //数据头不对，则重新开始寻找0x55数据头
//	{
//		ucRxCnt=0;
//		return;
//	}
//	if (ucRxCnt<11) {return;}//数据不满11个，则返回
//	else
//	{
//		switch(ucRxBuffer[1])//判断数据是哪种数据，然后将其拷贝到对应的结构体中，有些数据包需要通过上位机打开对应的输出后，才能接收到这个数据包的数据
//		{
//			case 0x50:	memcpy(&stcTime,&ucRxBuffer[2],8);break;//memcpy为编译器自带的内存拷贝函数，需引用"string.h"，将接收缓冲区的字符拷贝到数据结构体里面，从而实现数据的解析。
//			case 0x51:	memcpy(&stcAcc,&ucRxBuffer[2],8);break;
//			case 0x52:	memcpy(&stcGyro,&ucRxBuffer[2],8);break;
//			case 0x53:	memcpy(&stcAngle,&ucRxBuffer[2],8);break;
//			case 0x54:	memcpy(&stcMag,&ucRxBuffer[2],8);break;
//			case 0x55:	memcpy(&stcDStatus,&ucRxBuffer[2],8);break;
//			case 0x56:	memcpy(&stcPress,&ucRxBuffer[2],8);break;
//			case 0x57:	memcpy(&stcLonLat,&ucRxBuffer[2],8);break;
//			case 0x58:	memcpy(&stcGPSV,&ucRxBuffer[2],8);break;
//			case 0x59:	memcpy(&stcQ,&ucRxBuffer[2],8);break;
//		}
//		ucRxCnt=0;//清空缓存区
//	}
//}
