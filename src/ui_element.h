#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H
#include "screenpos.h"

typedef struct UIElement UIElement;

typedef void (*UIDrawFn)(const UIElement* el);
typedef void (*UIResizeFn)(UIElement* el, int w, int h);

struct UIElement {
    ScreenPos  pos;
    UIDrawFn draw;
    UIResizeFn resize;
    void       *impl;
};
#endif
/*

Impl contains what the struct actually is. I.e instantiated subtype of the interface.

UIElement el;
el.impl = malloc(sizeof(struct Button));

The draw function is then assigned based on what type of UIElement we have.
In that function, we extract the exact type using the below code.

void button_draw(const UIElement *el) {
    struct Button *btn = el->impl;
    ...
}

*/