//
// Created by Whisky on 2023/7/26.
//

#include "common_inc.h"

My_Adc Adc(&hadc1 , &htim2);
AdvancedMeasure advanced_measure;
AdvancedMeasure advanced_measure2;
GraphWindows signal_graph(10, 40, 130, 40+100, LGRAY);
GraphWindows signal_graph2(140, 40, 260, 40+100, LGRAY);
InfoWindows basic_info(10, 122+20, 90, 187+20, LGRAYBLUE);
InfoWindows basic_info2(140, 122+20, 140+80, 187+20, LGRAYBLUE);
void adc_process();

void MainPage_show()
{
    lcd_show_string_config(95,40,_lcddev.width, _lcddev.height, LCD_FONTSIZE_2412, (char *)"TOTO TEAM", YELLOW, LCD_MODE_BACKFILLED);
    ScreenWindows button_FreqSet(40, 90, 270, 90+50, LIGHTBLUE);
    ScreenWindows button_GraphShow(40, 110+50, 270, 110+100,LIGHTBLUE);
    button_FreqSet.refresh().add_frame(RED).add_text("Freq Set", MAGENTA, - 25);
    button_GraphShow.refresh().add_frame(RED).add_text("Show Graph", MAGENTA, - 25);

    while (1)
    {
        tp_dev.scan(0);

        if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
        {
            if(get_botton(button_FreqSet))
            {
                delay_ms(100);
                lcd_clear();
                currentPage = FREQ_SET;
                break;
            }
            if(get_botton(button_GraphShow))
            {
                delay_ms(100);
                lcd_clear();
                currentPage = GRAPH_SHOW;
                break;
            }
        }

        else delay_ms(10);	//没有按键按下的时候
    }
}

ScreenWindows button_1(40, 60 -15, 80, 100-15, CYAN);
ScreenWindows button_4(40, 100 + 10-15 , 80 , 100 + 40 + 10-15, CYAN);
ScreenWindows button_7(40, 150 + 10-15 , 80 , 150 + 40 + 10-15, CYAN);
ScreenWindows button_f(40, 150 + 40 + 10 + 10 -15, 80 , 150 + 40 + 10 + 10 + 40-15, CYAN);
ScreenWindows button_2(80 + 10, 60-15, 80 + 10 + 40, 100-15, CYAN);
ScreenWindows button_5(80 + 10, 100 + 10-15 , 80 + 10 + 40 , 100 + 40 + 10-15, CYAN);
ScreenWindows button_8(80 + 10, 150 + 10-15 , 80 + 10 + 40 , 150 + 40 + 10-15, CYAN);
ScreenWindows button_0(80 + 10, 150 + 40 + 10 + 10 -15, 80 + 10 + 40 , 150 + 40 + 10 + 10 + 40-15, CYAN);
ScreenWindows button_3(130 + 10, 60-15, 130 + 10 + 40, 100-15, CYAN);
ScreenWindows button_6(130 + 10, 100 + 10-15 , 130 + 10 + 40 , 100 + 40 + 10-15, CYAN);
ScreenWindows button_9(130 + 10, 150 + 10 -15, 130 + 10 + 40 , 150 + 40 + 10-15, CYAN);
ScreenWindows button_r(130 + 10, 150 + 40 + 10 + 10 -15, 130 + 10 + 40 , 150 + 40 + 10 + 10 + 40-15, CYAN);

uint8_t get_button_num()
{
    if(get_botton(button_1))
        return 1;
    else if(get_botton(button_2))
        return 2;
    else if(get_botton(button_3))
        return 3;
    else if(get_botton(button_4))
        return 4;
    else if(get_botton(button_5))
        return 5;
    else if(get_botton(button_6))
        return 6;
    else if(get_botton(button_7))
        return 7;
    else if(get_botton(button_8))
        return 8;
    else if(get_botton(button_9))
        return 9;
    else if(get_botton(button_0))
        return 0;
    else
        return 0xfe;
}
void FreqSet_show()
{
    ScreenWindows button_back(10, 10, 60, 35, LIGHTBLUE);
    button_back.refresh().add_frame(RED).add_text("Back",MAGENTA, -15);
    ScreenWindows button_sweep(200, 180, 270 , 180+ 50, CYAN);

    button_1.refresh().add_text("1",MAGENTA, - 3);
    button_4.refresh().add_text("4",MAGENTA, - 3);
    button_7.refresh().add_text("7",MAGENTA, - 3);
    button_2.refresh().add_text("2",MAGENTA, - 3);
    button_5.refresh().add_text("5",MAGENTA, - 3);
    button_8.refresh().add_text("8",MAGENTA, - 3);
    button_0.refresh().add_text("0",MAGENTA, - 3);
    button_3.refresh().add_text("3",MAGENTA, - 3);
    button_6.refresh().add_text("6",MAGENTA, - 3);
    button_9.refresh().add_text("9",MAGENTA, - 3);
    button_r.refresh().add_text("E",MAGENTA, - 3);
    button_f.refresh().add_text("C",MAGENTA, - 3);
    button_sweep.refresh().add_text("SWEEP",MAGENTA, - 18);
    bool nofirst = true;
    uint32_t freq;
    painter.color = BLACK;
    lcd_show_string_config(200,10,_lcddev.width,_lcddev.height, LCD_FONTSIZE_2412,(char *)"Freq:", BLACK, LCD_MODE_BACKFILLED);
    while (1)
    {
        tp_dev.scan(0);

        if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
        {
            if(get_botton(button_back))
            {
                lcd_clear();
                currentPage = MAIN_PAGE;
                break;
            }

            if (get_botton(button_f))
            {
                freq = 0;
                nofirst = true;
                lcd_show_num(200, 50 , freq, 10, .mode = LCD_MODE_BACKFILLED);
                uint8_t temp = painter.mode;
                painter.mode = LCD_MODE_BACKFILLED;
                lcd_show_string(200, 90, "   ");
                painter.mode = temp;
            }

            if (get_botton(button_r))
            {
                lcd_show_string(200, 90, "OUT");
            }

            if (get_botton(button_sweep))
            {
                lcd_show_string(200, 90, "OUT");
            }

            uint8_t num = get_button_num();
            if ( num != 0xfe)
            {
                delay_ms(100);
                if (nofirst)
                {
                    freq = num;
                    nofirst = false;
                }
                else
                    freq = freq * 10 + num;
                if (freq >= 2000000000)
                {
                    uint8_t temp = painter.mode;
                    painter.mode = LCD_MODE_BACKFILLED;
                    lcd_show_string(200, 50, "ERROR            ");
                    freq = 0;
                    nofirst = true;
                    painter.mode = temp;
                }
                else
                    lcd_show_num(200, 50 , freq, 10, .mode = LCD_MODE_BACKFILLED);
                delay_ms(100);
            }
        }

        else delay_ms(10);	//没有按键按下的时候
    }
}


void GraphShow_show()
{


    signal_graph.add_frame(CYAN);
    signal_graph2.add_frame(CYAN);

    ScreenWindows button_back(10, 10, 60, 35, LIGHTBLUE);
    button_back.refresh().add_frame(RED).add_text("Back",MAGENTA, -15);

    Adc.init(409600, 72000000).start();

    while (1)
    {
        tp_dev.scan(0);

        if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
        {
            if(get_botton(button_back))
            {
                lcd_clear();
                currentPage = MAIN_PAGE;
                Adc.stop();
                break;
            }
        }

        if (Adc.is_finished())
        {
             adc_process();
        }
    }
}
uint32_t adc_ch1[ADC_BUFF_SIZE/2] = {0};
uint32_t adc_ch2[ADC_BUFF_SIZE/2] = {0};
void adc_process()
{
    Adc.get_signal(2, My_Adc_Channel_No_1, adc_ch1);
    Adc.get_signal(2, My_Adc_Channel_No_2, adc_ch2);
    advanced_measure.init(adc_ch1, ADC_BUFF_SIZE / 2);
    advanced_measure2.init(adc_ch2, ADC_BUFF_SIZE / 2);
    signal_graph.refresh().add_ref_axis(LIGHTGREEN).graph(advanced_measure, YELLOW , ADC_BUFF_SIZE / 2);
    signal_graph2.refresh().add_ref_axis(LIGHTGREEN).graph(advanced_measure2, MAGENTA , ADC_BUFF_SIZE / 2);
    basic_info.refresh().show_basic(advanced_measure, BRRED);
    basic_info2.refresh().show_basic(advanced_measure2, BRRED);
    Adc.start();
}



