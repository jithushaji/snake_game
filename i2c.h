/* 
 * File:   i2c.h
 * Author: neo
 *
 * Created on May 17, 2021, 8:33 AM
 */

#ifndef I2C_H
#define	I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

#define STRT_SND        0x08 
#define SCL_CLK         100000UL   
    
void i2c_start();
void i2c_stop();
void i2c_init(); 
void i2c_write(char);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

