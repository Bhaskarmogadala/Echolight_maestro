#include <lpc214x.h>
#include "rtc_echo.h"
#include "types.h"
#include "lcd_defines.h"
#include "lcd.h"

// Array to hold names of days of the week
char week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};



/*
Initialize the Real-Time Clock (RTC)
This function disables the RTC, sets the prescaler values, 
and then enables the RTC.
*/
void RTC_Init(void) 
{
  // Disable and reset the RTC
	CCR = RTC_RESET;
  
  #if (CPU == LPC2129)	
  // Set prescaler integer and fractional parts
	PREINT = PREINT_VAL;
	PREFRAC = PREFRAC_VAL;
	CCR = RTC_ENABLE; 
	#elif(CPU == LPC2148)
  // Enable the RTC
	CCR = RTC_ENABLE | RTC_CLKSRC;  
	#endif
  
}

/*
Get the current RTC time
hour Pointer to store the current hour
minute Pointer to store the current minute
second Pointer to store the current second
*/

void SetRTCHour(u32 hour)
{
	HOUR=hour;
}
void SetRTCMin(u32 min)
{
	MIN=min;
}
void SetRTCSec(u32 sec)
{
	SEC=sec;
}

/*
Set the RTC date
day of month to set (1 31)
month to set (1 12)
year to set (four digits)
*/

void SetRTCDate(u32 date)
{
	DOM = date;
}
void SetRTCMonth(u32 month)
{
	MONTH = month;
}
void SetRTCYear(u32 year)
{
	YEAR = year;
}

/*
Set the day of the week in RTC
Day of Week to set (0=Sunday, ..., 6=Saturday)
*/
void SetRTCDay(u32 day)
{
	DOW = day;
}

/*
Get the current RTC time
hour Pointer to store the current hour
minute Pointer to store the current minute
second Pointer to store the current second
*/
void GetRTCHour(s32 *hour)
{
	*hour = HOUR;
}
void GetRTCMin(s32 *minute)
{
	*minute = MIN;
}
void GetRTCSec(s32 *second)
{
	*second = SEC;
}


/*
Get the current RTC date
day Pointer to store the current date (1 31)
month Pointer to store the current month (1 12)
year Pointer to store the current year (four digits)
*/
void GetRTCDate(s32 *date)
{
	*date = DOM;
}
void GetRTCMonth(s32 *month)
{
	*month = MONTH;
}
void GetRTCYear(s32 *year)
{
	*year = YEAR;
}

/*
Get the current day of the week
dow Pointer to store Day of Week (0=Sunday, ..., 6=Saturday)
*/
void GetRTCDay(s32 *day)
{
	*day = DOW;
} 

/*
Display the RTC time on LCD
hour value (0 23)
minute value (0 59)
second value (0 59) seperated by ':'
*/
void DisplayRTCTime(u32 hour, u32 minute, u32 second)
{
	CmdLCD(GOTO_LINE1_POS0);
	CharLCD((hour/10)+48);
	CharLCD((hour%10)+48);
	CharLCD(':');
	CharLCD((minute/10)+48);
	CharLCD((minute%10)+48);
	CharLCD(':');
	CharLCD((second/10)+48);
	CharLCD((second%10)+48);
}


/*
Display the RTC date on LCD
Day of month (1 31)
Month (1 12)
Year (four digits) and seperated by '/'
*/
void DisplayRTCDate(u32 date, u32 month, u32 year)
{
	CmdLCD(GOTO_LINE2_POS0);
	CharLCD((date/10)+48);
	CharLCD((date%10)+48);
	CharLCD('/');
	CharLCD((month/10)+48);
	CharLCD((month%10)+48);
	CharLCD('/');
	U32LCD(year);
}

/*
Display the current day of the week on LCD
dow (Day of Week) (0=Sunday, ..., 6=Saturday)
*/
void DisplayRTCDay(u32 day)
{
	CmdLCD(GOTO_LINE1_POS0+10);
	StrLCD(week[day]);
  
}
