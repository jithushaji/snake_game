/* 
 * File:   oled,h.h
 * Author: neo
 *
 * Created on May 18, 2021, 12:19 PM
 */

#ifndef OLED_H_H
#define	OLED_H_H

#ifdef	__cplusplus
extern "C" {
#endif

#define OLED_ADDR            0x78    
    
#define SND_CMD              0x00
#define SND_DATA             0x40    
    
#define OLED_ON              0xAF
#define OLED_OFF             0xAE
#define NORM_DISP            0xA6 
#define INV_DISP             0xA7 
#define SET_ADDR_MODE        0x20 
#define PAGE_MODE            0x02 
#define HORIZ_MODE           0x00 
#define VERTI_MODE           0x01 
#define SET_COL_ADDR		 0x21
#define SET_PAGE_ADDR        0x22
#define SET_CLK_DIV          0xD5
#define SET_MUX_RATIO        0xA8
#define SET_DISP_OFST        0xD3
#define STRT_LINE            0x40
#define SET_CHRG_PMP         0x8D
#define DISP_ON_RSUM         0xA4
#define SET_CONTRST          0x81    
#define SET_COM_CONF         0xDA    
#define SET_PRECHRG          0xD9
#define SET_VCOM_DCT         0xDB
#define SET_SEG_REMAP        0xA0
#define COM_SCAN_NOR        0xC0    
    
    
    

 
    
void oled_init();    
void oled_cmd(char);
void oled_data(char);
void set_cursor(char,char);
void set_pixel(char,char);
void oled_clear();
void set_colum();
void set_page();
void display_off();
void display_on();
void oled_all_on();    
    
#ifdef	__cplusplus
}
#endif

#endif	/* OLED_H_H */

