
#ifndef MAIN_HEADER_H
#define MAIN_HEADER_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define TILE_NUM    9

#define TILE_BLANK  0
#define TILE_LAND   1
#define TILE_HILL   2
#define TILE_WATER  3
#define TILE_GRASS  4
#define TILE_OK     5
#define TILE_BAD    6
#define TILE_RAIL_STRAIGHT  7
#define TILE_RAIL_CORNER    8

#define OBJ_NUM         4

#define OBJ_ENEMY       0
#define OBJ_TOWER       1
#define OBJ_TOWER_GUN   2
#define OBJ_BUILDING    3

#define FONTS_NUM   1

extern ALLEGRO_EVENT_QUEUE* event_queue;
extern ALLEGRO_EVENT event;
extern ALLEGRO_TIMER* timer;
extern ALLEGRO_DISPLAY* display;
extern ALLEGRO_FONT *fonts[FONTS_NUM];
extern struct globals_t globals;

struct xy_t {
    int x;
    int y;
};

struct game_state_t{
    bool end_game;
    bool grid_en;
    bool build_menu_on;
    bool tower0_en;
    bool tower0_place;
    bool tower1_en;
    bool tower1_place;
    bool house0_en;
    bool house0_place;
    bool house1_en;
    bool house1_place;
    int zoom;
    struct xy_t screen_center;
    float screen_step;
    int screen_w;
    int screen_h;
    int side_menu_w;
    int top_bar_h;
    float credits;
    float energy_produced;
    float energy_required;
};

struct keys_t{
    bool key_up;
    bool key_down;
    bool key_left;
    bool key_right;
    bool key_z;
    bool key_g;
    bool key_b;
    bool key_e;
};

struct mouse_t{
    bool lb;
    bool rb;
    int x;
    int y;
    int grid_x;
    int grid_y;
    int tile_x;
    int tile_y;
    int dx;
    int dy;
    int dz;
    int tile_info;
    bool is_rail;
    bool is_river;
    bool is_struct;
};

struct tiles_t {
    ALLEGRO_BITMAP *tile[TILE_NUM];
    int *p;
    int tile_size;
    int tile_w;
    int tile_h;
    struct xy_t map_center;
};

struct enemy_t{
    struct xy_t position;
    int path_num;
    float speed;
    float max_health;
    float health;
    int credits;
    struct enemy_t *prev;
    struct enemy_t *next;
};

struct tower_t{
    struct xy_t position;
    float angle;
    float damage;
    bool fire_active;
    int level;
    float range;
    struct enemy_t *target;
    struct tower_t *prev;
    struct tower_t *next;
};

struct building_t{
    struct xy_t position;
    float gold_per_tick;
    int level;
    struct building_t *prev;
    struct building_t *next;
};

struct structures_t{
    struct tower_t *t;
    struct building_t *b;
};


struct path_t{
    bool is_set;
    struct xy_t pos;
    struct xy_t pos_prev;
    struct xy_t pos_next;
};

struct float_text_t{
    int x;
    int y;
    int move_per_tick;
    int timeout;
    char text[20];
    struct float_text_t *prev;
    struct float_text_t *next;
};

struct globals_t {
    struct keys_t keys;
    struct mouse_t mouse;
    struct game_state_t game_state;
    struct tiles_t tiles;
    struct enemy_t *enemy;
    int enemy_num;
    bool enemy_spawn;
    struct tower_t *towers;
    struct building_t *buildings;
    struct structures_t *structures;
    ALLEGRO_BITMAP *objects[OBJ_NUM];
    struct path_t *river;
    struct path_t *rail;
    struct xy_t rail_start;
    struct xy_t rail_finish;
    bool place_object_active;
    struct float_text_t *float_text;

};

#include "draw_graphics.h"
#include "game_logic.h"
#include "input.h"
#include "llist.h"

#endif
