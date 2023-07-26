//
// Created by Whisky on 2023/7/25.
//

#ifndef HELLOWORLD_GUI_H
#define HELLOWORLD_GUI_H
#include "Screen.h"

extern PageName currentPage;

//Page
extern Page MainPage;
extern Page FreqSet;
extern Page GraphShow;

bool get_botton(ScreenWindows &button);

void MainPage_show();
void FreqSet_show();
void GraphShow_show();

#endif //HELLOWORLD_GUI_H
