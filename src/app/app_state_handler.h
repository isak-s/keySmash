#ifndef APP_STATE_HANDLER_H
#define APP_STATE_HANDLER_H
#include "app_context.h"

void app_handle_startup(AppContext* app);
void app_handle_new_test(AppContext* app);
void app_handle_in_test(AppContext* app);
void app_handle_test_finished(AppContext* app);
void app_handle_replay(AppContext* app);
void app_handle_quit(AppContext* app);
#endif