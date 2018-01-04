
#ifndef MAIN_HEADER_H
#define MAIN_HEADER_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "allegro5/allegro_image.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define GAME_UPADTES_PER_SEC 60

#define TILE_DEFSIZE    64

#define TILE_NUM    7

#define TILE_BLANK  0
#define TILE_LAND   1
#define TILE_HILL   2
#define TILE_WATER  3
#define TILE_GRASS  4
#define TILE_RAIL_STRAIGHT  5
#define TILE_RAIL_CORNER    6

#define TILE_ID_HILL_0  0x2
#define TILE_ID_HILL_1  0x4
#define TILE_ID_HILL_2  0x8
#define TILE_ID_HILL_3  0x10
#define TILE_ID_HILL_4  0x20
#define TILE_ID_HILL_5  0x40
#define TILE_ID_HILL_6  0x80
#define TILE_ID_HILL_7  0x100
#define TILE_ID_HILL_8  0x200
#define TILE_ID_HILL_9  0x400
#define TILE_ID_HILL_10 0x800
#define TILE_ID_HILL_11 0x1000
#define TILE_ID_HILL_12 0x2000
#define TILE_ID_HILL_13 0x4000
#define TILE_ID_HILL_14 0x8000
#define TILE_ID_HILL_15 0x10000
#define TILE_ID_HILL_16 0x20000

#define OBJ_NUM         4

#define OBJ_ENEMY       0
#define OBJ_TOWER       1
#define OBJ_TOWER_GUN   2
#define OBJ_BUILDING    3

#define UI_NUM 3

#define UI_BUILD_OK    0
#define UI_BUILD_BAD   1
#define UI_TWR_RANGE   2

#define FONTS_NUM   1

#define LLIST_ENEMY 0
#define LLIST_TOWER 1
#define LLIST_FLOAT_TEXT 2

#define MAX_ZOOM 2.0
#define MIN_ZOOM 0.5

extern ALLEGRO_EVENT_QUEUE* event_queue;
extern ALLEGRO_EVENT event;
extern ALLEGRO_TIMER* timer;
extern ALLEGRO_DISPLAY* display;
extern ALLEGRO_FONT *fonts[FONTS_NUM];
extern struct globals_t globals;

void abort_game(const char* message);

struct xy_t {
    int x;
    int y;
};

struct game_state_t{
    bool end_game;
    bool grid_en;
    bool build_menu_on;
    bool debug_on;
    bool tower0_en;
    bool tower0_place;
    bool tower1_en;
    bool tower1_place;
    bool house0_en;
    bool house0_place;
    bool house1_en;
    bool house1_place;
    int zoom;
    float zoom_mult;
    struct xy_t screen_center;
    float screen_step;
    int screen_w;
    int screen_h;
    int side_menu_w;
    int top_bar_h;
    float credits;
    float energy_produced;
    float energy_required;
    int count_down;
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
    bool key_d;
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
    int hill_info;
    bool is_rail;
    bool is_river;
    bool is_struct;
};

struct tiles_t {
    ALLEGRO_BITMAP *tile[TILE_NUM];
    int *p;
    int *hill;
    int tile_w;
    int tile_h;
    struct xy_t map_center;
};

struct llist_t {
    void *ptr;
    void *prev;
    void *next;
};

struct enemy_t{
    struct xy_t position;
    int path_num;
    float speed;
    float max_health;
    float health;
    int credits;
};

struct tower_t{
    struct xy_t position;
    float angle;
    float damage;
    bool fire_active;
    int level;
    float range;
    int price;
    struct enemy_t *target;
};

struct tower_list_t{
    struct tower_t *tower0;
    struct tower_t *tower1;
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
    ALLEGRO_COLOR colour;
};

struct globals_t {
    struct keys_t keys;
    struct mouse_t mouse;
    struct game_state_t game_state;
    struct tiles_t tiles;
    struct llist_t *enemy;
    int enemy_num;
    bool enemy_spawn;
    struct llist_t *towers;
    struct tower_list_t *tower_list;
    struct building_t *buildings;
    struct structures_t *structures;
    ALLEGRO_BITMAP *objects[OBJ_NUM];
    ALLEGRO_BITMAP *ui_items[UI_NUM];
    struct path_t *river;
    struct path_t *rail;
    struct xy_t rail_start;
    struct xy_t rail_finish;
    struct llist_t *float_text;

};

#include "draw_graphics.h"
#include "game_logic.h"
#include "map_generator.h"
#include "input.h"
#include "llist.h"

#endif
