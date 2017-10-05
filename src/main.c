
#include "main_header.h"
#include <stdio.h>
#include <stdlib.h>
#include "draw_graphics.h"
#include "game_logic.h"
#include "input.h"

ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_EVENT event;
ALLEGRO_TIMER* timer;
ALLEGRO_DISPLAY* display;

struct globals_t globals;

void abort_game(const char* message)
{
    printf("%s \n", message);
    exit(1);
}

void init(void)
{
    if (!al_init())
        abort_game("Failed to initialize allegro");

    if (!al_install_keyboard())
        abort_game("Failed to install keyboard");

    if (!al_install_mouse())
        abort_game("Failed to install mouse");

    timer = al_create_timer(1.0 / 60);
    if (!timer)
        abort_game("Failed to create timer");

    al_set_new_display_flags(ALLEGRO_WINDOWED);
    display = al_create_display(800, 600);
    if (!display)
        abort_game("Failed to create display");

    event_queue = al_create_event_queue();
    if (!event_queue)
        abort_game("Failed to create event queue");

    if (!al_init_primitives_addon())
        abort_game("Failed to initialize allegro addons");

    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));

    //initialize random with time
    srand(time(NULL));

    init_globals();
    init_graphics();
    init_logic();
}

void shutdown(void)
{
    if (timer)
        al_destroy_timer(timer);

    if (display)
        al_destroy_display(display);

    if (event_queue)
        al_destroy_event_queue(event_queue);


    //free all llist objects
    //enemy
    while(globals.enemy != NULL){
        globals.enemy = remove_ll_item(globals.enemy,globals.enemy);
    }
    //towers
    while(globals.towers != NULL){
        globals.towers = t_remove_ll_item(globals.towers,globals.towers);
    }
    //buildings
}

void game_loop(void)
{
    bool redraw = true;
    al_start_timer(timer);

    while (!globals.game_state.end_game) {

        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
            update_logic();
        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            get_keyboard_input();
        }
        else if (event.type == ALLEGRO_EVENT_KEY_UP){
            reset_keyboard_input();
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_AXES){
            get_mouse_move();
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            set_mouse_button();
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            reset_mouse_button();
        }
        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            update_graphics();
            al_flip_display();
        }


    }
}

int main(int argc, char* argv[])
{
    init();
    game_loop();
    shutdown();

    return 0;
}
