#include<avr/io.h>
#include<xc.h>

#include "oled.h"
#include "i2c.h"
#include "button.h"

int main()
{
    //sei();
    PCMSK0 = 0x00;
    PCMSK1 = 0x00;
    PCMSK2 = 0x00;
    
    SREG |= 0x80;
    oled_init();
    draw_box();
    
    set_pixel(64,32);
    set_button(20);
    
    
    while(1);
    return(0);
}


