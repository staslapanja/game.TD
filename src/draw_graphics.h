#ifndef DRAW_GRAPHICS_H
#define DRAW_GRAPHICS_H

#include "main_header.h"

void create_tiles(void);
void create_game_objects(void);
void create_ui_items(void);
void init_graphics(void);
void update_graphics(void);
void draw_background(void);
void draw_map(void);
void draw_hill(float x, float y, int hill_type, int tile_size);
void draw_rail(void);
void draw_cursor_rect(void);
void draw_tower_range(float x, float y, float range);
void draw_top_bar(void);
void draw_side_menu(void);
void draw_bottom_bar(void);
void draw_enemy(void);
void draw_health_bar(float x, float y, int len, float max, float value);
void draw_towers(void);
void draw_floating_text(void);
void draw_debug(void);

#endif
