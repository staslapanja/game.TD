#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "main_header.h"

void init_globals(void);
void init_tiles(int w, int h);
void init_structures(void);
void move_camera(float x, float y);
void zoom_to_camera_pos(float x, float y);
void create_river(void);
void create_rail(void);
void create_tower_list(void);
void keyboard_actions(void);
void mouse_actions(void);
bool mouse_menu_check(float x0, float y0, float x1, float y1);
bool mouse_inside_map_screen(void);
void mouse_to_grid(void);
void get_cursor_info(void);
bool price_check(void);
bool place_check(void);
void place_object_on_map(void);
void set_zoom_tile_size(void);
void mouse_clear_diff(void);
void bound_screen_inside_virtual_map(void);
void update_enemy(void);
void update_enemy_path(struct enemy_t *a);
bool check_enemy_finish(struct enemy_t *a);
void update_towers(void);
void update_float_text(void);
void update_timers(void);
void init_logic(void);
void update_logic(void);

#endif
