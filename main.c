#include "oled.h"
#include "i2c.h"

void draw_box();

int main()
{
    oled_init();
    draw_box();
    
    set_pixel(64,32);
    
    set_pixel(24,13);
    set_pixel(24,12);
    set_pixel(24,11);
    set_pixel(24,10);
    set_pixel(24,9);
    set_pixel(24,8);
    set_pixel(25,8);
    set_pixel(26,8);
    set_pixel(27,8);
    set_pixel(28,8);
    
    return(0);
}


void draw_box()
{
    int i;
    
        for(i=0;i<64;i++)
    {
       set_pixel(0,i); 
       set_pixel(127,i); 
    }

    for(i=0;i<128;i++)
    {
       set_pixel(i,63); 
       set_pixel(i,0); 
    }
}