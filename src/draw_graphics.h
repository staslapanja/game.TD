#ifndef DRAW_GRAPHICS_H
#define DRAW_GRAPHICS_H

#include "main_header.h"

void create_tiles(void);
void create_game_objects(void);
void update_graphics(void);
void draw_background(void);
void draw_map(void);
void draw_cursor_rect(void);
void draw_build_menu(void);
void draw_enemy(void);
void draw_health_bar(float x, float y, int len, float max, float value);
void draw_towers(void);

#endif
