#include "app_state_handler.h"

int main(void) {
    AppContext app = { .state = APP_STARTUP };

    while(app.state != APP_TERMINATED) {
        switch (app.state)
        {
        case APP_STARTUP:       app_handle_startup(&app);       break;
        case APP_NEW_TEST:      app_handle_new_test(&app);      break;
        case APP_IN_TEST:       app_handle_in_test(&app);       break;
        case APP_TEST_FINISHED: app_handle_test_finished(&app); break;
        case APP_QUIT:          app_handle_quit(&app);          break;
        default:                                                break;
        }
        app.state = app.next_state;
    }
    return 0;
}
