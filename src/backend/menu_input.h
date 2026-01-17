#ifndef INPUT_H
#define INPUT_H

/* handle special characters like tab and arrow keys.
If alphanumerical, return a TypingTestInput */
typedef enum {
    M_ARROW_UP,
    M_ARROW_DOWN,
    M_ARROW_LEFT,
    M_ARROW_RIGHT,
    M_TAB,
    M_SHIFT_TAB,
    M_ENTER
} MenuInputType;

typedef struct {
    MenuInputType type;
} MenuInput;

#endif
