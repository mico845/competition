//
// Created by Whisky on 2023/7/25.
//

#include "PageWindows.h"



void Page::show(void (*fnptr)(void)) {
    _fnptr = fnptr;
    if (fnptr != nullptr)
        fnptr();
}

void Page::show() {
    if (_fnptr != nullptr)
        _fnptr();
}

void Page::back(Page &otherPage) {
    otherPage.show();
}



