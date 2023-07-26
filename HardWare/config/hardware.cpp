//
// Created by Whisky on 2023/7/25.
//

#include "hardware.h"

void hardware_init()
{
    lcd_init();
    painter.size = LCD_FONTSIZE_1608;
    lcd_clear();
    //start_demos();
    painter.back_color= GRAY;
    painter.color = BROWN;
    painter.mode = LCD_MODE_NO_BACKFILLED;
    lcd_clear();


    W25QXX_Init();

    while(W25QXX_ReadID()!=W25Q16)								//检测不到W25QXX
    {
        lcd_show_string(30,150,"W25Q16 Check Failed!");
        delay_ms(1000);
        lcd_show_string(30,150,"Please Check!      ");
        delay_ms(1000);
    }
    //lcd_show_string(30,150,"W25Q16 Ready!");
    //delay_ms(500);
    lcd_clear();
    tp_dev.init();				//触摸屏初始化

}
