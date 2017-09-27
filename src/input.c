
#include "input.h"
#include "main_header.h"

void get_keyboard_input(void)
{
    if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
        globals.game_state.end_game = true;
    }
    if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
        globals.keys.key_up = true;
    }
    if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
        globals.keys.key_down = true;
    }
    if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
        globals.keys.key_left = true;
    }
    if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
        globals.keys.key_right = true;
    }
    if (event.keyboard.keycode == ALLEGRO_KEY_Z) {
        globals.keys.key_z = true;
    }
    if (event.keyboard.keycode == ALLEGRO_KEY_G) {
        globals.keys.key_g = true;
    }
    if (event.keyboard.keycode == ALLEGRO_KEY_B) {
        globals.keys.key_b = true;
    }
}

void reset_keyboard_input(void)
{
    if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
        globals.game_state.end_game = true;
    }
    if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
        globals.keys.key_up = false;
    }
    if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
        globals.keys.key_down = false;
    }
    if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
        globals.keys.key_left = false;
    }
    if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
        globals.keys.key_right = false;
    }

}

void get_mouse_move(void)
{
    globals.mouse.x = event.mouse.x;
    globals.mouse.y = event.mouse.y;

    globals.mouse.dx += event.mouse.dx;
    globals.mouse.dy += event.mouse.dy;
    globals.mouse.dz += event.mouse.dz;

}

void set_mouse_button(void)
{
    if (event.mouse.button & 0x1){
        globals.mouse.lb = true;
    }
    if (event.mouse.button & 0x2){
        globals.mouse.rb = true;
    }
}

void reset_mouse_button(void)
{
    if (event.mouse.button & 0x1){
        globals.mouse.lb = false;
    }
    if (event.mouse.button & 0x2){
        globals.mouse.rb = false;
    }
}
