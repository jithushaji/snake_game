#define F_CPU 1600000UL
#include <avr/interrupt.h>
#include<util/delay.h>
#define len 7
#include "oled.h"


int y_pos = 0;
int x_pos = 0;
int tail;
int delay = 1000;
static int begin_x = 1, end_x = len;
static int begin_y = 1, end_y = len;
int R, L;
static int k = 0;

void set_button(int x) {
    sei();
    int msk = x / 8;
    int pin = x % 8;

    DDRD = 1 << DDD4;
    PORTD = 1 << PD4;

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

void move_init() {
    int i, j;
    y_pos = begin_y;

    while (begin_x < 128) 
    {

        if (R == 0)
            return; //returning to main()

        if (((begin_x-1) > 0)&&(end_x < 127)) 
        {

            for (i = begin_x; i <= end_x; i++) 
            {
                set_pixel(i, y_pos); //making snake
                clear_pixel((begin_x - 1), y_pos); //clearing trail pixel while adding head pixel 
            }
            _delay_ms(delay);
        }

        
        if (end_x == 127) 
        {

            for (j = 0; j < len; j++) 
            {
                clear_pixel(end_x - (len - j), y_pos);   
                _delay_ms(delay);
                set_pixel(j + 1, y_pos); //making snake   
            }

            begin_x = 1;
            end_x = len;
        }    

        end_x++;
        begin_x++;        
    }
}

void move_up() {
    int i, j;
    
    tail = begin_x-1;
    x_pos = end_x-1;

    while (begin_y < 64) 
    {
        
        if (L == 0)
            return;

        if (((begin_y-1) > 0)&&(end_y-1 < 63)) 
        {
            for (i = begin_y; i < end_y; i++) 
            {               
                set_pixel(x_pos, i); 
                if((x_pos-tail) >= 0)
                {
                    clear_pixel(tail,y_pos);
                    _delay_ms(delay);
                    tail++;
                }
                else
                {
                clear_pixel(x_pos, begin_y - 1);              
                }
            }
            _delay_ms(delay);
        }                             
        

        if (end_y == 63) //reseting at Y end of display
        {
            for(j=0;j<len;j++)
            {
            clear_pixel(x_pos, end_y-(len-j));
            _delay_ms(delay);
            set_pixel(x_pos, j+1);
            
            }

            begin_y = 1;
            end_y = len;
        }
        
        end_y++;
        begin_y++;        
    }
}

ISR(PCINT2_vect) 
{
    R = 0;
    L = 1;
    int i;
       
    if (k == 0)
    {
        k = 1;
        for(i=begin_y;i<end_y;i++)
        {   if(x_pos>0)
            clear_pixel(x_pos,i);
        }
        if (x_pos >= 127)
            x_pos = 1;
        x_pos++;
    } 
    else if (k > 0) 
    {
        k = 0;
    }
}