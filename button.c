#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include "oled.h"


void set_button(int x) 
{
    sei();
    int msk = x / 8;
    int pin = x % 8;
    
    DDRD = 1<<DDD4 ;
    PORTD = 1<<PD4;
    
    
    PCICR |= 1 << msk; 
    switch (msk) {
        case 0:
            PCMSK0 |= 1 << pin;
            break;
        case 1:
            PCMSK1 |= 1 << pin;
            break;
        case 2:
            PCMSK2 |= 1 << pin;
            break;
    }
}

ISR(PCINT2_vect) {

    static unsigned int x = 1, y = 1;
    static int count = 0;
    int len = 5;
    static int end;
    
    count++;
    set_pixel(x, y);
    
    if ((end == 1)&&(x <= len)) 
        clear_pixel(((126 - len) + x), y-1);  // making the tail disappear while snake comes out of box start
    else
        end = 0;
    
    if ((x - len) >= 1)
        clear_pixel(x - len, y); // clear the tail pixel while  snake move forward

    if (count == 1) {  // move to next line
        if (x < 126)
            x++;
        else if (x >= 126) {
            
            x = 1;
            end = 1;
            y++;
        }

        PORTD = 1 << PD4;
    } else
        count = 0; // to remove triggering pin change interrupt twice for every key press  

}