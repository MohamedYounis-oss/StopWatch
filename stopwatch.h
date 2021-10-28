/*
 * stopWatch.h
 *
 * Created: 10/25/2021 9:37:02 PM
 *  Author: Mohamed Younis
 */ 
#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#define SEG_PORT PORTA

#define SEG_CTRL_PORT PORTC
#define COM1_PIN 6
#define COM2_PIN 7

#define BUTTONS_PIN PIND
#define BUT1_PIN 2
#define BUT2_PIN 3
#define BUT3_PIN 4
#define BUT4_PIN 5

void my_delay_ms(u16 n);
void multi_seg_display(u8 num);
void buzzer(void);


#endif /* STOPWATCH_H_ */