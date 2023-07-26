//
// Created by Whisky on 2023/6/1.
//

#include "ScreenWindows.h"


ScreenWindows& ScreenWindows::refresh() {
    ScreenBase::refresh();
    return *this;
}

ScreenWindows &ScreenWindows::add_frame(uint16_t color) {
    ScreenBase::add_frame(color);
    return *this;
}

ScreenWindows &ScreenWindows::add_text(const char *text, uint16_t color, int x_offset, int y_offset) {
    uint16_t temp = painter.color;
    painter.color = color;
    uint8_t font_height;
    uint8_t font_width = painter.width;
    if (font_width == 12)
        font_height = 6;
    else if (font_width == 16)
        font_height = 8;
    else if (font_width == 24)
        font_height = 12;
    else
        font_height = 16;
    lcd_show_string((_sx + (_ex - _sx) / 2 + x_offset), _sy + (_ey - _sy)/2 - font_height/2+ y_offset, (char *)text);
    painter.color = temp;
    return *this;
}


