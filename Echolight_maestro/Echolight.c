#include <LPC214x.h>
#include "defines.h"
#include "types.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "rtc_echo.h"
#include "delay.h"
#include "eint0_echo.h"
#include "kpm.h"
#include "kpm_defines.h"
#include "adc.h"
#include "adc_defines.h"
#include "pin_connect_block.h"
#define EINT3_PIN 30
#define EINT3_FUN 2
#define EINT3_INT 17
volatile u32 setflag=0;
void enable_eint3(void);
u32 num,key;
void displaytime(void);
void editinfo(void);
void SetRTCHourinfo(void);
void SetRTCMinuteinfo(void);
void SetRTCSecondsinfo(void);
void SetRTCDateinfo(void);
void SetRTCMonthinfo(void);
void SetRTCYearinfo(void );
s32 hour,min,sec,date,month,year,day;
char ch;
f32 eAR;
u32 adcDVal;
u8 menuActive = 0;
int main()
{
	IODIR1= 1<<24;
	enable_eint3();
	// Initialize RTC
	RTC_Init();
	// Initialize Kyepad
	Init_kpm();
	//Initialize ADC
	Init_ADC();
    //Initialize the LCD
	InitLCD();
	// Set the initial time (hours, minutes, seconds)
	SetRTCHour(5);
	SetRTCMin(15);
	SetRTCSec(05);
	SetRTCDate(01);
	SetRTCMonth(9);
	SetRTCYear(25);
	SetRTCDay(4);
	while(1)
	{
		if(!menuActive)
		{
			displaytime();
			if((hour >= 18 && hour <= 23) || (hour >= 0 && hour < 6))  
			{
				// Time is between 18:00 and 06:00
				// Night time: show light output + ADC value
				delay_MS(2);
				CmdLCD(GOTO_LINE2_POS0+11);
				Read_ADC(1,&adcDVal,&eAR);
				F32LCD(eAR,3);
				if(eAR > 1.5)
        		{
            		IOSET1 = 1<<24;   // Turn ON LED
					delay_MS(20);
        		}
        		else
        		{
            		IOCLR1 = 1<<24;   // Turn OFF LED
					delay_MS(20);
        		}
			}
			if (!((hour >= 18 && hour <= 23) || (hour >= 0 && hour < 6)))
			{	
				// Time is between 06:00 and 18:00	
				// Day time: show RTC time/date only
        		delay_MS(2);
        		displaytime();
			}
			if(setflag == 1)
			{
				setflag=0;
				menuActive = 1;          // menu mode
				while(READBIT(IOPIN0,16)==0);
				delay_MS(100);
				CmdLCD(CLEAR_LCD);
				CmdLCD(GOTO_LINE1_POS0);
				StrLCD("1.EDIT RTC INFO");
				CmdLCD(GOTO_LINE2_POS0);
				StrLCD("2.EXIT");
				delay_MS(100);
				ch=KeyScan();
				delay_MS(100);
				CmdLCD(CLEAR_LCD);
				CmdLCD(GOTO_LINE1_POS0);
				switch(ch)
				{
					case '1':editinfo();
									break;
					case '2':StrLCD("2.Exit");
									menuActive = 0;      // exit menu
									break;
				}
			}
			
		}
	}
}

void displaytime(void)
{
	// Get and display the current time on LCD
	GetRTCHour(&hour);
	GetRTCMin(&min);
	GetRTCSec(&sec);
	DisplayRTCTime(hour,min,sec);
	GetRTCDate(&date);
	GetRTCMonth(&month);
	GetRTCYear(&year);
	DisplayRTCDate(date,month,year);
	GetRTCDay(&day);
	DisplayRTCDay(day);
}
void editinfo(void)
{
	while(1)
	{
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("1-Hr ");
	StrLCD("2-Min ");
	StrLCD("3-Sec");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("4-DD ");
	StrLCD("5-Mon ");
	StrLCD("6-yr");
	delay_MS(100);
	ch=KeyScan();
	delay_MS(50);
	switch(ch)
	{
		case '1':
					SetRTCHourinfo();
					break;
		case '2':
					SetRTCMinuteinfo();
					break;
    	case '3':
    		        SetRTCSecondsinfo();
					break;
    	case '4':
            		SetRTCDateinfo();
					break;
    	case '5':
            		SetRTCMonthinfo();
					break;
    	case '6':
            		SetRTCYearinfo();
					break;
		case '0':
					menuActive = 0; 
					CmdLCD(CLEAR_LCD);
            		return ;
		}
	}
}
void SetRTCHourinfo(void)
{
	CmdLCD(CLEAR_LCD);
    CmdLCD(GOTO_LINE1_POS0);
	StrLCD("Enter Hour:");
    ReadNum(&num, &ch);     // wait for number input from keypad
    // Show what you entered
    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("New Hr:");
    U32LCD(num);           // function to display number (you likely have it in lcd.c)

    SetRTCHour(num);        // update RTC
    delay_MS(500);
	CmdLCD(CLEAR_LCD);
}
void SetRTCMinuteinfo(void)
{
	CmdLCD(CLEAR_LCD);
    CmdLCD(GOTO_LINE1_POS0);
	StrLCD("Enter Minute:");
    ReadNum(&num, &ch);     // wait for number input from keypad
    // Show what you entered
    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("New Min:");
    U32LCD(num);           // function to display number (you likely have it in lcd.c)
    SetRTCMin(num);        // update RTC
    delay_MS(500);
	CmdLCD(CLEAR_LCD);
}
void SetRTCSecondsinfo(void)
{
	CmdLCD(CLEAR_LCD);
    CmdLCD(GOTO_LINE1_POS0);
	StrLCD("Enter Sec:");
    ReadNum(&num, &ch);     // wait for number input from keypad
    // Show what you entered
    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("New Sec:");
    U32LCD(num);           // function to display number (you likely have it in lcd.c)
    SetRTCSec(num);        // update RTC
    delay_MS(500);
	CmdLCD(CLEAR_LCD);
}
void SetRTCDateinfo(void)
{
	CmdLCD(CLEAR_LCD);
    CmdLCD(GOTO_LINE1_POS0);
	StrLCD("Enter Date:");
    ReadNum(&num, &ch);     // wait for number input from keypad
    // Show what you entered
    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("New Date:");
    U32LCD(num);           // function to display number (you likely have it in lcd.c)

    SetRTCDate(num);        // update RTC
    delay_MS(500);
	CmdLCD(CLEAR_LCD);
}
void SetRTCMonthinfo(void)
{
	CmdLCD(CLEAR_LCD);
    CmdLCD(GOTO_LINE1_POS0);
	StrLCD("Enter Mon:");
    ReadNum(&num, &ch);     // wait for number input from keypad
    // Show what you entered
    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("New Mon:");
    U32LCD(num);           // function to display number (you likely have it in lcd.c)

    SetRTCMonth(num);        // update RTC
    delay_MS(500);
	CmdLCD(CLEAR_LCD);
}
void SetRTCYearinfo(void )
{
	CmdLCD(CLEAR_LCD);
    CmdLCD(GOTO_LINE1_POS0);
	StrLCD("Enter Year:");
    ReadNum(&num, &ch);     // wait for number input from keypad
    // Show what you entered
    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("New Year:");
    U32LCD(num);           // function to display number (you likely have it in lcd.c)

    SetRTCYear(num);        // update RTC
    delay_MS(500);
	CmdLCD(CLEAR_LCD);
}
void eint3_isr(void)__irq
{
	setflag=1;
	EXTINT=1<<3;
	VICVectAddr=0;
}
void enable_eint3(void)
{
	cfgportpinfunc(0,EINT3_PIN,EINT3_FUN);
	VICIntSelect=0;
	
	VICIntEnable=1<<EINT3_INT;
	VICVectCntl1=(1<<5)|EINT3_INT;
	VICVectAddr1 = (unsigned int)eint3_isr;
	
	EXTMODE=1<<3;
	EXTPOLAR=0<<3;
}


