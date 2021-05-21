#include "i2c.h"
#include "oled.h"


void oled_init()
{
    i2c_init();
    oled_cmd(OLED_OFF);         // display off 
    oled_cmd(SET_MUX_RATIO);    // mux ratio for frame frequency formula  {F =F osc/(D � K � No.of Mux)}
    oled_cmd(0x3F);             // power on reset value is 64 (0x3F)
    oled_cmd(SET_DISP_OFST);    // set vertical shift
    oled_cmd(0x00);             // no offset
    oled_cmd(STRT_LINE);        // range from 0 to 63 (0x40 - 0x7F) 
    oled_cmd(SET_SEG_REMAP|0x1);
    oled_cmd(COM_SCAN_NOR);     // set COM scan direction to normal
    oled_cmd(SET_COM_CONF);     // sequential COM or alternate COM, enable or disable COM left/right remap
    oled_cmd(0x12);             // set to alternate COM and disable remap
    oled_cmd(SET_CONTRST);      // contrast setting
    oled_cmd(0x00);             // range from 0x00 to 0xFF
    oled_cmd(DISP_ON_RSUM); 
    oled_cmd(NORM_DISP);        // normal display mode
    oled_cmd(SET_CLK_DIV);      // set oscillator frequency & display clock division
    oled_cmd(0x80);             // A[7:4] oscillator frequency ; A[3:0] clock division 1-16
    oled_cmd(SET_CHRG_PMP);     // enable or disable charge pump regulator
    oled_cmd(0x14);             // turn on
    oled_cmd(OLED_ON);          // display on
    
    oled_clear();
}

void oled_cmd(char data)
{
    i2c_start();
    i2c_write(OLED_ADDR);
    i2c_write(SND_CMD);         // indicates next byte is command
    i2c_write(data);
    i2c_stop();
}

void oled_data(char data)
{
    i2c_start();
    i2c_write(OLED_ADDR);
    i2c_write(SND_DATA);         // indicates next byte is command
    i2c_write(data);
    i2c_stop();
}

void oled_clear()
{
  unsigned char i,k;
	for(k=0;k<8;k++)
	{
		set_cursor(k,0);
		{
			for(i=0;i<130;i++)           
			{
				oled_data(0x00);         //clear all COL
			}
		}
	}
}

void oled_all_on()
{
  unsigned char i,k;
	for(k=0;k<8;k++)
	{
		set_cursor(k,0);
		{
			for(i=0;i<130;i++)           
			{
				oled_data(0xFF);         //clear all COL
			}
		}
	}
}

void set_colum()
{
    oled_cmd(SET_COL_ADDR);
    oled_cmd(0);
    oled_cmd(130);
}

void set_page()
{
    oled_cmd(SET_PAGE_ADDR);
    oled_cmd(0);
    oled_cmd(7);
}

void display_off()
{
    oled_cmd(OLED_OFF);
}

void display_on()
{
    oled_cmd(OLED_ON);
}

void set_cursor(char row, char col)
{
    oled_cmd(0xB0|row);                 // set Page
	oled_cmd(0x00+(col&0x0F));          // set low col address
	oled_cmd(0x10+((col>>4)&0x0F));     // set high col address  
}

void set_pixel(char x, char y)
{
    int page,pos;
    static char buff[8][128] = {0};
    page = y/8;
    pos = y%8;
    x = x+2;
    buff[page][x]|=(0x01<<pos);
    oled_cmd(0xB0|page);              // set Page
    oled_cmd(0x00|((x)&0x0F));          // set low col address
	oled_cmd(0x10|(((x)>>4)&0x0F));     // set high col address
    
    oled_data(buff[page][x]);                // set bit
    
}



