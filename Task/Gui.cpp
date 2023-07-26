//
// Created by Whisky on 2023/7/26.
//
#include "Gui.h"


PageName currentPage = MAIN_PAGE;
Page FreqSet(FREQ_SET, &FreqSet_show);
Page GraphShow(GRAPH_SHOW, &GraphShow_show);
Page MainPage(MAIN_PAGE, &MainPage_show);

bool get_botton(ScreenWindows &button)
{
    if(tp_dev.x[0] < button._ex && tp_dev.y[0] < button._ey && tp_dev.x[0] > button._sx && tp_dev.y[0] > button._sy)
        return true;
    else
        return false;
}

