#include <ncurses.h>
#include "ui_panel_curses.h"
#include "menu_adapter.h"
#include "time.h"
#include <stdlib.h>
#include "ui_commands.h"

// make this a contract and then have subtypes such as englishtest and such maybe
typedef struct {
    long  start_timestamp;
    char* text;
    char* language;
    int idx;
} TypingTest;

TypingTest new_english_typing_test(char* text)
{
    return (TypingTest){
        .idx = 0,
        .language = "english",
        .text = text,
        .start_timestamp = time(NULL)
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

    int element_count = 4;
    UIPanel menu = {
        .width = max_x-10,  // 5 char padding on each side
        .height = element_count + 2, // for border
        .x = 5,
        .y = 2,
        .element_count = element_count
    };

    MenuItem item1 = { .text = "Start typing", .enabled = true };
    MenuItem item2 = { .text = "Statistics", .enabled = true };
    MenuItem item4 = { .text = "Mode", .enabled = true };
    MenuItem item3 = { .text = "QUIT", .enabled = true };

    UIElement elements[element_count];
    elements[0] = ui_menu_item_create(&item1);
    elements[1] = ui_menu_item_create(&item2);
    elements[2] = ui_menu_item_create(&item4);
    elements[3] = ui_menu_item_create(&item3);

    menu.elements = elements;

    // curses wrapper main menu
    UIPanelCurses pc = ui_panel_curses_create(&menu);

    ui_panel_curses_draw(&pc);

    wrefresh(pc.win);

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

    ui_panel_curses_destroy(&pc);
    endwin();
    return 0;
}
