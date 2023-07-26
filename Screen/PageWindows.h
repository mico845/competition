//
// Created by Whisky on 2023/7/25.
//

#ifndef HELLOWORLD_PAGEWINDOWS_H
#define HELLOWORLD_PAGEWINDOWS_H
#include "main.h"

typedef enum {
    MAIN_PAGE = 0,
    FREQ_SET,
    GRAPH_SHOW
}PageName;


class Page
{
public:
    Page(PageName page_name, void (*fnptr)(void)) {  _page_name = page_name; _fnptr = fnptr; }

    void show();
    void show(void (*fnptr)(void));
    void back(Page& otherPage);
    PageName get_PageName(void) {return _page_name; };
private:
    void (*_fnptr)(void) = nullptr;
    PageName _page_name;
};

#endif //HELLOWORLD_PAGEWINDOWS_H
