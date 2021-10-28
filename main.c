/*
 * stopwatch.c
 *
 * Created: 10/25/2021 9:27:52 PM
 * Author : Mohamed Younis
 */ 

#include "MemMap.h"
#include "Utils.h"
#include "StdTypes.h"
#include "stopWatch.h"

extern u8 first_delay;
extern u8 second_delay;

int main(void)
{
	
	u8 second = 30;
        u16 delay;
	u8 but1_pushed = 0;
	u8 but2_pushed = 0;
	u8 but3_pushed = 0;
	u8 but4_pushed = 0;
	u8 pause = 0;
	u8 calibration_mode = 0;
	u8 inc_dec = 1;
	
	
	// multiplexed 7segment
	DDRA = 0xff;
	PORTA = 0;
	
	// multiplexed 7segment com1, com2 && buzzer
	DDRC = 0xff;
	PORTC = 0;
	
	//buttons
	DDRD = 0;
	PORTD = 0xff;
	
	
	
    while (1) 
    {
		

						
		for(delay = 0; delay<250; delay++){
			
			multi_seg_display(second);	
			
			
			// Pause button || increase button
			if (GET_BIT(BUTTONS_PIN, BUT1_PIN) == 0)
			{
				if (but1_pushed == 0){
					
					if (calibration_mode == 1)
					{
						second += inc_dec;
						but1_pushed = 1;
						
					} else {
						
						pause ^= 1;
						but1_pushed = 1;

						if (pause){
							break;
						}
						
					}
				}	
			}
			else{
				but1_pushed = 0;
			}
			
			
			
			// reset button || decrease button 
			if (GET_BIT(BUTTONS_PIN, BUT2_PIN) == 0)
			{
				
				if (!but2_pushed){
					
					if (calibration_mode == 1)
					{
						second -= inc_dec;
						but2_pushed = 1;
						
					} else {
						second = 31;
						buzzer();
						but2_pushed = 1;
						break;
					}
					
				}
					
			} else {
				but2_pushed = 0;
			}
			
			
			
			// into calibration mode button
			if (GET_BIT(BUTTONS_PIN, BUT3_PIN) == 0)
			{
				
				if (!but3_pushed)
				{
					calibration_mode ^= 1;
					pause ^= 1;
					but3_pushed = 1;
					second_delay = 2;
					first_delay = 2;
				}
				
			}else {
				
				but3_pushed = 0;
				
			}
			
			
			
			// switch between units and tens
			if (GET_BIT(BUTTONS_PIN, BUT4_PIN) == 0 && calibration_mode==1)
			{
				
				if (!but4_pushed)
				{
					if (inc_dec == 1){
						inc_dec = 10;
						second_delay = 30;
						first_delay = 2;
					} else if (inc_dec == 10){
						inc_dec = 1;
						second_delay = 2;
						first_delay = 30;
					}
					but4_pushed = 1;
				}
				
			}else {
				
				but4_pushed = 0;
				
			}
								
		}
		
		
		
		
		if (pause == 0){
			
			second--;
			if (second == 255){
				SEG_PORT = 0;
				
				buzzer();
				
				break;
			}
			
		}
					
    }
}

