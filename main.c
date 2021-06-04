
#include<avr/io.h>


#include "oled.h"
#include "i2c.h"
#include "button.h"



extern int R,L;

//int R = 0;
//int L = 0;

int main()
{
    //sei();
    PCMSK0 = 0x00;
    PCMSK1 = 0x00;
    PCMSK2 = 0x00;
    
    SREG |= 0x80;
    oled_init();
    draw_box();
    
    for(int i =0;i<62;i++)
    {
       set_pixel(64,i); 
    }
 
    set_button(20);
  
    R = 1;
    
    while(1)
    {
        if ((R == 1)&&(L == 0))
            move_right();

        if ((R == 0)&&(L == 1))
            move_up();
    }
    return(0);
}


