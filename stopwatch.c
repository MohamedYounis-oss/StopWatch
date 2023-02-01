/*
 * stopWatch.c
 *
 * Created: 10/25/2021 9:36:48 PM
 *  Author: Mohamed Younis
 */ 

#include "MemMap.h"
#include "Utils.h"
#include "StdTypes.h"
#include "stopWatch.h"

u8 first_delay = 2;
u8 second_delay = 2;

const unsigned char segment_numbers[10] = {0x3f, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0xFF, 0x6F};
	
void my_delay_ms(u16 n)
{
	
	while(n--)
	{
		_delay_ms(1);
	}
}


void multi_seg_display(u8 num){
	
	if (num > 99)
	{
		return;
	}
	
	int y = num%10;		// units
	int x = num/10;		// tens
	
	SET_BIT(SEG_CTRL_PORT, COM2_PIN);
	CLEAR_BIT(SEG_CTRL_PORT, COM1_PIN);		
			
	SEG_PORT = segment_numbers[x]<<1;
	my_delay_ms(first_delay);
	
	SET_BIT(SEG_CTRL_PORT, COM1_PIN);		
	CLEAR_BIT(SEG_CTRL_PORT, COM2_PIN);	
	SEG_PORT = segment_numbers[y]<<1;
	my_delay_ms(second_delay);	
}


void buzzer(void)
{
	for (u8 buz=0; buz<2; buz++)
	{
		SET_BIT(PORTC, 5);
		_delay_ms(150);
		CLEAR_BIT(PORTC, 5);
		_delay_ms(150);
	}
}
