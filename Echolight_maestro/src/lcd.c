#include<LPC21xx.h>
#include "lcd_defines.h"
#include "delay.h"
#include "defines.h"
void WriteLCD(unsigned char anyByte)
{
	IOCLR0=1<<LCD_RW;
	WRITEBYTE(IOPIN0,LCD_DATA,anyByte);
	IOSET0=1<<LCD_EN;
	delay_US(1);
	IOCLR0=1<<LCD_EN;
	delay_MS(2);
}
void CharLCD(unsigned char asciiVal)
{
	IOSET0=1<<LCD_RS;
	WriteLCD(asciiVal);
}
void CmdLCD(unsigned char cmd)
{
	IOCLR0=1<<LCD_RS;
	WriteLCD(cmd);
	delay_MS(2);
}
void InitLCD(void)
{
	IODIR0|=(0xFF<<LCD_DATA)|(1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN);
	delay_MS(15);
	CmdLCD(0x30);
	delay_MS(4);
	delay_US(100);
	CmdLCD(0x30);
	delay_US(100);
	CmdLCD(0x30);
	CmdLCD(MODE_8BIT_2LINE);
	CmdLCD(DSP_ON_CUR_OFF);
	CmdLCD(CLEAR_LCD);
	CmdLCD(SHIFT_CUR_RIGHT);
}
void StrLCD(char *p)
{
	while(*p)
	{
		CharLCD(*p++);
		delay_US(37);
	}
}
void U32LCD(unsigned int num)
{
	unsigned char a[10];
	int i=0;
	if(num==0)
	CharLCD('0');
	else
	{
		while(num>0)
		{
			a[i]=(num%10)+48;
			i++;
			num/=10;
		}
		for(--i;i>=0;i--)
		{
			CharLCD(a[i]);
		}
	}
}
void S32LCD(int snum)
{
	if(snum>0)
	{
		CharLCD('-');
		snum=-snum;
	}
	U32LCD(snum);
}
void F32LCD(float fnum,unsigned char nDP)
{
	unsigned int num,i;
	if(fnum<0.0)
	{
		CharLCD('-');
		fnum=-fnum;
	}
	num=fnum;
	U32LCD(num);
	CharLCD('.');
	for(i=0;i<nDP;i++)
	{
		fnum=(fnum-num)*10;
		num=fnum;
		CharLCD(num+48);
	}
}
void BuildCGRAM(unsigned char *p,unsigned char nBytes)
{
	unsigned int i;
	CmdLCD(GOTO_CGRAM_START);
	IOSET0=1<<LCD_RS;
	for(i=0;i<nBytes;i++)
	{
		WriteLCD(p[i]);
	}
	IOCLR0= 1<<LCD_RS;
	CmdLCD(GOTO_LINE1_POS0);
}
