#include<LPC21xx.h>
#include "delay.h"
#include "adc_defines.h"
#include "pin_connect_block.h"
void Init_ADC(void)
{
	cfgportpinfunc(0,28,1);//0x15400000
	ADCR=((CLKDIV<<CLKDIV_BITS)|(1<<PDN_BIT));
}
void Read_ADC(unsigned int chNo,unsigned int *adcDVal,float *eAR)
{
	ADCR&=0xFFFFFF00;
	ADCR|=(1<<chNo)|(1<<ADC_CONV_START_BIT);
	delay_US(3);
	while(((ADDR>>DONE_BIT)&1)==0);
	ADCR&=~(1<<ADC_CONV_START_BIT);
	*adcDVal=((ADDR>>DIGITAL_DATA_BITS)&1023);
	*eAR=(*adcDVal*(3.3/1024));
}
