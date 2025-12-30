#include <ncurses.h>
#include "ui_panel_curses.h"
#include "menu_adapter.h"
#include "time.h"
#include <stdlib.h>
#include "ui_commands.h"

#include "menu.h"


// make this a contract and then have subtypes such as englishtest and such maybe

#include "fifo_queue.h"
typedef struct {
    long  start_timestamp;
    char* text;
    char* language;
    int idx;

    FifoQueue draw_queue;
    FifoQueue input_history;
} TypingTest;

TypingTest new_english_typing_test(char* text)
{
    return (TypingTest){
        .idx = 0,
        .language = "english",
        .text = text,
        .start_timestamp = time(NULL),
        .draw_queue = fifo_q_new(),
        .input_history = fifo_q_new()
    };
}

/* this should be the template */
typedef struct TypingTestInput {
    bool is_correct;
    int  time_since_test_start;
    // has to be an int since there are other non-alphabetic keycodes.
    int inputted;
} TypingTestInput;

DrawCommand draw_command_from_input(TypingTestInput* inp)
{
    if (inp->inputted == KEY_BACKSPACE || inp->inputted == KEY_DC) {
        return new_delete_char_command();
    } else if (!inp->is_correct) {
        return new_draw_char_command(inp->inputted);  // draw_incorrect_char_command
    } else {
        return new_draw_char_command(inp->inputted);
    }
}

/* This function will await until a char is inputted. Halts the rest of the program!!! */
TypingTestInput get_input(TypingTest* tt)
{
    TypingTestInput input;
    input.inputted = getch();
    input.time_since_test_start = time(NULL) - tt->start_timestamp;
    input.is_correct = (tt->text[tt->idx] == input.inputted);
    return input;
}

int main(void) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    refresh();
    // logical panel

    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);

    UIPanelCurses main_menu = menu_main_create(max_x);

    ui_panel_curses_draw(&main_menu);
    wrefresh(main_menu.win);

    UIPanel test_area = {
        .width = max_x - 10,
        .height = max_y / 3,
        .x = 5,
        .y = 9,
        .element_count = 0
    };

    UIPanelCurses ta = ui_panel_curses_create(&test_area);

    ui_panel_curses_draw(&ta);
    wrefresh(ta.win);

    wmove(ta.win, 1, 1);
    DrawCommand dc = new_draw_char_command('A');
    dc.execute(&dc, ta.win);
    wmove(ta.win, 1, 4);
    dc = new_draw_char_command('B');

    dc.execute(&dc, ta.win);
    wrefresh(ta.win);

    TypingTest tt = new_english_typing_test("this is an example typing test");
    // iterate over all chars in the text, and create draw commands for all of them.
    // Then reset index, and the user types over the already written text, but in a different color.

    int cx = 1;
    int cy = 2;
    char c = ' ';
    while(c != 'q') {
        wmove(ta.win, cy, cx++);
        TypingTestInput inp = get_input(&tt);
        DrawCommand dc = draw_command_from_input(&inp);
        dc.execute(&dc, ta.win);

        wrefresh(ta.win);

        if (cx >= ta.panel->width-1) { // - 1 for border
            cy++;
            cx = 1;
        }
    }
    free(main_menu.panel->elements);
    // free(main_menu.panel);
    ui_panel_curses_destroy(&main_menu);
    ui_panel_curses_destroy(&ta);
    endwin();
    return 0;
}
