#include<avr/io.h>
#include "i2c.h"


void i2c_init() 
{
    TWSR = 0x00;    
    TWCR = TWCR = (1 << TWEN);
    TWBR = 0x0C;    //SCL to 400kHz
    //TWBR = ((F_CPU/SCL_CLK)-16)/2;    // Bit rate   
}

void i2c_write(char data)
{
    TWDR = data; 
    TWCR = (1 << TWINT) | (1 << TWEN);
    while(!(TWCR & (1 << TWINT))); 
}

void i2c_start()
{
    i2c_init(); 
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    while(!(TWCR & (1 << TWINT))); 
}

void i2c_stop()
{
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO); 
}




