# A typing test game for people terminally in the terminal

first install curses:
    sudo apt-get install libncurses-dev

TODO:
- [ ] draw current word in separate box refresh upon hitting space

- [ ] create structs for different elements that can be resized based on terminal size.

- [ ] implement state machine with in test, and in menu
    - [ ] in test: text in the middle of the screen. one button for reset test. One button for menu. graph for showing statistics. pressing menu button changes state and view to menu.
    - [ ] in menu: buttons for different modes. Buttons for settings. Buttons for statistics.
    - [ ] Pressing up/down arrow cycles between selected menu item. enter to activate.
        - [ ] Restart
        - [ ] exit
        - [ ] new game
- [x] color scheme
- [x] store all typing commands in some datastructure so that the test can be replayed afterfards.
        If the user types the correct character, it is marked in gray. If it is incorrect, it is marked red. Then the cursor moves one step to the right and should wrap if the text is overflowing.
- [ ] auto generate problems.
- [ ] misc
