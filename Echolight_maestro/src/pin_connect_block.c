#include<lpc21xx.h>
void cfgportpinfunc(unsigned int portNO,unsigned int pinNO,unsigned int pinfunc)
{
 	if(portNO==0)
	{
		if(pinNO<=15)
		{
				PINSEL0=(PINSEL0&~(3<<pinNO*2))|(pinfunc<<(pinNO*2));
		}
		if((pinNO>=16) && (pinNO<=31))
		{
				PINSEL1=(PINSEL1&~(3<<(pinNO-16)*2))|(pinfunc<<((pinNO-16)*2));
		}
	}
	else if(portNO==1)
	{
		if((pinNO>=16) && (pinNO<=31))
		{
			   	PINSEL2=(PINSEL2&~(3<<(pinNO-16)*2))|(pinfunc<<((pinNO-16)*2));
		}
	}
}

