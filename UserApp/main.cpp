//
// Created by Whisky on 2023/5/16.
//
#include "common_inc.h"

void Main()
{
    Init();

    for (;;) {
        switch(currentPage)
        {
            case MAIN_PAGE:
                MainPage.show();
                break;
            case FREQ_SET:
                FreqSet.show();
                break;
            case GRAPH_SHOW:
                GraphShow.show();
                break;
        }

    }
}
