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


////CopeSerialDataΪ����1�жϵ��ú���������ÿ�յ�һ�����ݣ�����һ�����������
//void CopeSerial1Data(void)
//{
//	
//	uint8 res;
//	uart_getchar(UART_1, &res);//��ȡ����
//	static unsigned char ucRxBuffer[250];
//	static unsigned char ucRxCnt = 0;	
//	
//	
//	
////	LED_REVERSE();					//���յ����ݣ�LED����˸һ��
//	ucRxBuffer[ucRxCnt++]=res;	//���յ������ݴ��뻺������
//	if (ucRxBuffer[0]!=0x55) //����ͷ���ԣ������¿�ʼѰ��0x55����ͷ
//	{
//		ucRxCnt=0;
//		return;
//	}
//	if (ucRxCnt<11) {return;}//���ݲ���11�����򷵻�
//	else
//	{
//		switch(ucRxBuffer[1])//�ж��������������ݣ�Ȼ���俽������Ӧ�Ľṹ���У���Щ���ݰ���Ҫͨ����λ���򿪶�Ӧ������󣬲��ܽ��յ�������ݰ�������
//		{
//			case 0x50:	memcpy(&stcTime,&ucRxBuffer[2],8);break;//memcpyΪ�������Դ����ڴ濽��������������"string.h"�������ջ��������ַ����������ݽṹ�����棬�Ӷ�ʵ�����ݵĽ�����
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
//		ucRxCnt=0;//��ջ�����
//	}
//}
