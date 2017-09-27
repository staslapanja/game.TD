
#ifndef MAIN_HEADER_H
#define MAIN_HEADER_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#define TILE_NUM    5

#define TILE_BLANK  0
#define TILE_LAND   1
#define TILE_HILL   2
#define TILE_WATER  3
#define TILE_GRASS  4

extern ALLEGRO_EVENT_QUEUE* event_queue;
extern ALLEGRO_EVENT event;
extern ALLEGRO_TIMER* timer;
extern ALLEGRO_DISPLAY* display;
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
    bool tower1_en;
    bool house0_en;
    bool house1_en;
    int zoom;
    struct xy_t screen_center;
    float screen_step;
    int screen_w;
    int screen_h;
    int side_menu_w;
};

struct keys_t{
    bool key_up;
    bool key_down;
    bool key_left;
    bool key_right;
    bool key_z;
    bool key_g;
    bool key_b;
};

struct mouse_t{
    bool lb;
    bool rb;
    int x;
    int y;
    int dx;
    int dy;
    int dz;
};

struct tiles_t {
    ALLEGRO_BITMAP *tile[TILE_NUM];
    int *p;
    int tile_size;
    int tile_w;
    int tile_h;
    struct xy_t map_center;
};

struct globals_t {
    struct keys_t keys;
    struct mouse_t mouse;
    struct game_state_t game_state;
    struct tiles_t tiles;
};

#endif
