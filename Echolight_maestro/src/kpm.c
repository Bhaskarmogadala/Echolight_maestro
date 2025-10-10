#include<LPC21xx.h>
#include "kpm_defines.h"
#include "defines.h"
#include "lcd.h"
#include "types.h"
const unsigned char kpmLUT[4][4]=
{
	{'7','8','9','/'},
	{'4','5','6','*'},
	{'1','2','3','-'},
	{'C','0','=','+'}
};

void Init_kpm(void)
{
	IODIR1|=15<<ROW0;
}
unsigned int ColScan(void)
{
	unsigned int Status;
	Status=((READNIBBLE(IOPIN1,COL0))<15)?0:1;
	return Status;
}
unsigned int RowCheck(void)
{
	unsigned int r;
	for(r=0;r<=3;r++)
	{
		WRITENIBBLE(IOPIN1,ROW0,~(1<<r));
		if(ColScan()==0)
		break;
	}
	WRITENIBBLE(IOPIN1,ROW0,0);
	return r;
}
unsigned int ColCheck(void)
{
	unsigned int c;
	for(c=0;c<=3;c++)
	{
		if(READBIT(IOPIN1,(COL0+c))==0)
				break;
	}
	return c;
}

unsigned int KeyScan(void)
{
	unsigned int r,c,key;
	while(ColScan());
	r=RowCheck();
	c=ColCheck();
	key=kpmLUT[r][c];
	while(!ColScan());
	return key;
}
void ReadNum(u32 *num, char *lastKey)
{
    char buf[10];   // to store typed digits
    int i = 0,p=0;
    char key;
    *num = 0;

    while (1)
    {
        key = KeyScan();   // wait for key
        *lastKey = key;

        if (key >= '0' && key <= '9')   // digit entered
        {
            if (i < 9) {
                buf[i++] = key;
                buf[i] = '\0';

                CharLCD(key);   // show on LCD
            }
        }
        else if (key == 'C')    // backspace
        {
            if (i > 0) {
                i--;
                buf[i] = '\0';

                // LCD backspace: move cursor left, overwrite with space, move left again
                CmdLCD(0x10);  // cursor left
                CharLCD(' ');
                CmdLCD(0x10);  // cursor left again
            }
        }
        else if (key == '=')    // enter key
        {
            break;  // finish input
        }
    }

    // convert buffer to number
    for (p = 0; p < i; p++) {
        *num = (*num * 10) + (buf[p] - '0');
    }
}
