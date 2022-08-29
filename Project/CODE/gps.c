#include "gps.h"


//bool uart2_interrupt_flag = false;	

//char USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
uint8 uart2_get_buffer;
double a_latitude,b_longitude;
uint8 temp1,temp2;
char rxdatabufer;
u16 point1 = 0;

_SaveData Save_Data;//结构体定义

void clrStruct()
{
	Save_Data.isGetData = false;
	Save_Data.isParseData = false;
	Save_Data.isUsefull = false;
	memset(Save_Data.GPS_Buffer, 0, GPS_Buffer_Length);      //清空
	memset(Save_Data.UTCTime, 0, UTCTime_Length);
	memset(Save_Data.latitude, 0, latitude_Length);
	memset(Save_Data.N_S, 0, N_S_Length);
	memset(Save_Data.longitude, 0, longitude_Length);
	memset(Save_Data.E_W, 0, E_W_Length);
	
}//memset函数常与sizeof配合使用



void errorLog(int num)
{
	
	while (1)
	{
	  	printf("ERROR%d\r\n",num);
	}
}

void parseGpsBuffer()//对GPS数据进行解析
{
	char *subString;
	char *subStringNext;
	char i = 0;
	if(Save_Data.isGetData)
	{
			Save_Data.isGetData = false;
			for(i=0;i<=6;i++)
			{
					if(i==0)
					{
							if ((subString = strstr(Save_Data.GPS_Buffer, ",")) == NULL)//此处使用到了Save_Data.GPS_Buffer
							{
									errorLog(1);	//解析错误
							}
					}
					else
					{
							subString++;
							if ((subStringNext = strstr(subString, ",")) != NULL)
							{
									char usefullBuffer[2];
									switch(i)
									{
											case 1:memcpy(Save_Data.UTCTime, subString, subStringNext - subString);break;	//获取UTC时间
											case 2:memcpy(usefullBuffer, subString, subStringNext - subString);break;	//获取UTC时间
											case 3:memcpy(Save_Data.latitude, subString, subStringNext - subString);break;	//获取纬度信息
											case 4:memcpy(Save_Data.N_S, subString, subStringNext - subString);break;	//获取N/S
											case 5:memcpy(Save_Data.longitude, subString, subStringNext - subString);break;	//获取经度信息
											case 6:memcpy(Save_Data.E_W, subString, subStringNext - subString);break;	//获取E/W

											default:break;
									}
									subString = subStringNext;
									Save_Data.isParseData = true;
									if(usefullBuffer[0] == 'A')
									{
											Save_Data.isUsefull = true;
									}
									else if(usefullBuffer[0] == 'V')
									{
											Save_Data.isUsefull = false;
									}
									
							}
							else
							{
									errorLog(2);	//解析错误
							}
			}
		}

	}
}

void transform()
{
		a_latitude=atof(Save_Data.latitude);//字符型转换为浮点型，即可实现char[]转化为double
		b_longitude=atof(Save_Data.longitude);
}
