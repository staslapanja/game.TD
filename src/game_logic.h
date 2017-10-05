#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "main_header.h"
#include "llist.h"

void init_globals(void);
void init_tiles(int w, int h);
void move_screen(struct xy_t pos);
void create_map(void);
void create_river(void);
void create_rail(void);
void keyboard_actions(void);
void mouse_actions(void);
void set_zoom_level(void);
void mouse_clear_diff(void);
void bound_screen(void);
void update_enemy(void);
void update_enemy_path(struct enemy_t *a);
bool check_enemy_finish(struct enemy_t *a);
void update_towers(void);
void init_logic(void);
void update_logic(void);

#endif