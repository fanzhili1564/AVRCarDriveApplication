/*
 * LCD1602Drive.h
 *
 * Created: 2016/1/16 22:26:23
 *  Author: fanzl
 */ 
#include <util/delay.h>
#include "AVR_BIT_PORT.h"

#define __DELAY_BACKWARD_COMPATIBLE__ 



#define LCD1602_Set 0x38
#define LCD1602_Clear 0x01
#define LCD1602_Display 0x0f
#define LCD1602_Mode 0x06

#define LCD1602_1_Left 0x80
#define LCD1602_2_Left (0x80 + 0x40)
/*
typedef struct _bit_struct {
	unsigned char bit0 ;
	unsigned char bit1 ;
	unsigned char bit2 ;
	unsigned char bit3 ;
	unsigned char bit4 ;
	unsigned char bit5 ;
	unsigned char bit6 ;
	unsigned char bit7 ;
}bit_field;

#define GET_BITFIELD(addr) (*((volatile bit_field *) (addr)))

#define LCD_RS GET_BITFIELD(PORTA).bit2
#define LCD_RW GET_BITFIELD(PORTA).bit3
#define LCD_EN GET_BITFIELD(PORTA).bit4
*/

void Write_Lcd_Command( unsigned char Command ) {
	ClrPA(BIT2);
	_delay_ms(1);
	ClrPA(BIT3);
	_delay_ms(1);
	SetPA(BIT4);
	_delay_ms(1);
	PORTD = Command;
	_delay_ms(1);
	ClrPA(BIT4);
	_delay_ms(1);
}

void Write_Lcd_Data( unsigned char Data ) {
	SetPA(BIT2);
	_delay_ms(1);
	ClrPA(BIT3);
	_delay_ms(1);
	
	SetPA(BIT4);
	_delay_ms(1);
	PORTD = Data;
	_delay_ms(1);
	ClrPA(BIT4);
	_delay_ms(1);
	
}

void LCD1602_Init( void ) {
	DDRD = 0xff;
	PORTD = 0x00;
	Write_Lcd_Command( LCD1602_Set );
	_delay_ms(10);
	Write_Lcd_Command( LCD1602_Clear );
	_delay_ms(10);
	Write_Lcd_Command( LCD1602_Display );
	_delay_ms(10);
	Write_Lcd_Command( LCD1602_Mode );
	_delay_ms(10);
}

void LCD1602_Printerf( unsigned char line, unsigned char address, unsigned char Data ) {
	if ( line ) {
		Write_Lcd_Command(0xc0 + address );
		Write_Lcd_Data( Data );
	} else {
		Write_Lcd_Command( 0x80 + address );
		Write_Lcd_Data( Data );
	}
}
	
	void LCD1602_Display_Function( unsigned char *table ) {
		unsigned char i;
		Write_Lcd_Command( LCD1602_1_Left );
		_delay_ms(10);
		for( i = 0; i<16; i++ ) {
			Write_Lcd_Data( table[i]);
			_delay_ms(20);
		}
	}
