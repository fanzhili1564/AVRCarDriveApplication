/*
 * AVRCarDriverApplication.c
 *
 * Created: 2016/1/16 22:21:43
 *  Author: fanzl
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include "LCD1602Drive.h"

#define __DELAY_BACKWARD_COMPATIBLE__ 

#define uchar unsigned char
#define uint unsigned int

uchar wz[]={"QQ:262342506"};
uchar gd[]={"TE:13523332693"};

int main(void)
{
	
	uchar i;
	DDRA=0xff;
	PORTA=0xff;
	DDRD=0xff;
	PORTD=0xff;
	   //��ʱ
	LCD1602_Init();     //1602��ʼ��
	_delay_ms(5);
	Write_Lcd_Command(0x80);
	_delay_ms(5);
	for(i=0;i<12;i++)
	{
		Write_Lcd_Data(wz[i]);
		_delay_ms(3);
	}
	Write_Lcd_Command(0x80+0x40); 		//��������ָ�룬���ַ�����
	for(i=0;i<14;i++)
	{
		Write_Lcd_Data(gd[i]);
		_delay_ms(3); //������ʱ���Դﵽ��̬��Ч��
	}
}