
#include "game_logic.h"
#include "main_header.h"

void init_globals(void)
{
    //init keys
    globals.keys.key_up = false;
    globals.keys.key_down = false;
    globals.keys.key_left = false;
    globals.keys.key_right = false;
    globals.keys.key_z = false;
    globals.keys.key_g = false;
    globals.keys.key_b = false;
    //init mouse
    globals.mouse.lb = false;
    globals.mouse.rb = false;
    globals.mouse.x = 0;
    globals.mouse.y = 0;
    globals.mouse.dx = 0;
    globals.mouse.dy = 0;
    //init game states
    globals.game_state.end_game = false;
    globals.game_state.grid_en = false;
    globals.game_state.build_menu_on = false;
    globals.game_state.tower0_en = true;
    globals.game_state.tower1_en = false;
    globals.game_state.house0_en = true;
    globals.game_state.house1_en = false;
    globals.game_state.zoom = 1;
    globals.game_state.screen_center.x = 0;
    globals.game_state.screen_center.y = 0;
    globals.game_state.screen_step = 8;
    globals.game_state.screen_w = al_get_display_width(display);
    globals.game_state.screen_h = al_get_display_height(display);
    globals.game_state.side_menu_w = 182;
}

void init_tiles(int w, int h)
{
    //tile pointer memory
    globals.tiles.p = (int*)malloc(sizeof(int) * w * h);
    //set all entries to NULL
    int i;
    for (i = 0; i < w * h; i++){
        globals.tiles.p[i] = TILE_BLANK;
    }
    globals.tiles.tile_size = 64;
    globals.tiles.tile_w = w;
    globals.tiles.tile_h = h;
    //set the map centre
    globals.tiles.map_center.x = (w * 64)/2;
    globals.tiles.map_center.y = (h * 64)/2;
}

void move_screen(struct xy_t pos)
{
    globals.game_state.screen_center = pos;
}

void create_map(void)
{
    int h,w,sel;

    for (h = 0; h < globals.tiles.tile_h; h++){
        for (w = 0; w < globals.tiles.tile_w; w++){
            sel = rand()%(2)+1;
            globals.tiles.p[h*globals.tiles.tile_w + w] = sel;
        }
    }
}

void keyboard_actions(void)
{
    //zoom control
    if (globals.keys.key_z == true){
        if (globals.game_state.zoom == 2){
            globals.game_state.zoom = 0;
        } else {
            globals.game_state.zoom++;
        }

        globals.keys.key_z = false;
    }

    //screen move with keys
    if (globals.keys.key_right == true)
        globals.game_state.screen_center.x += globals.game_state.screen_step;
    if (globals.keys.key_left == true)
        globals.game_state.screen_center.x -= globals.game_state.screen_step;
    if (globals.keys.key_down == true)
        globals.game_state.screen_center.y += globals.game_state.screen_step;
    if (globals.keys.key_up == true)
        globals.game_state.screen_center.y -= globals.game_state.screen_step;

    //grid enable
    if (globals.keys.key_g == true){
        globals.game_state.grid_en = !globals.game_state.grid_en;
        globals.keys.key_g = false;
    }

    //side build menu enable
    if (globals.keys.key_b == true){
        globals.game_state.build_menu_on = !globals.game_state.build_menu_on;
        globals.keys.key_b = false;
        if (globals.game_state.build_menu_on == true){
            globals.game_state.screen_w -= globals.game_state.side_menu_w;
        } else {
            globals.game_state.screen_w = al_get_display_width(display);
        }
    }
}

void mouse_actions(void)
{
    //screen move with mouse if RB held
    if (globals.mouse.rb == true){
        //horizontal movement
        globals.game_state.screen_center.x -= globals.mouse.dx;
        //vertical movement
        globals.game_state.screen_center.y -= globals.mouse.dy;
    }
    
    //zoom control with mouse wheel
    if (globals.mouse.dz > 0){
        if (globals.game_state.zoom == 2){
            globals.game_state.zoom = 2;
        } else {
            globals.game_state.zoom++;
        }
    } else if (globals.mouse.dz < 0){
        if (globals.game_state.zoom == 0){
            globals.game_state.zoom = 0;
        } else {
            globals.game_state.zoom--;
        }       
    }
}

void set_zoom_level(void)
{
    switch(globals.game_state.zoom){
        case 0:
            globals.tiles.tile_size = 32;
            break;
        case 1:
            globals.tiles.tile_size = 64;
            break;
        case 2:
            globals.tiles.tile_size = 128;
            break;
        default:
            globals.tiles.tile_size = 32;
            break;
    }    
}

void mouse_clear_diff(void)
{
    globals.mouse.dx = 0;
    globals.mouse.dy = 0;
    globals.mouse.dz = 0;
}

void bound_screen(void)
{
    //correct if screen is out of bounds
    if (globals.game_state.screen_center.x < 0){
        globals.game_state.screen_center.x = 0;
    }
    if (globals.game_state.screen_center.x > (globals.tiles.tile_w * globals.tiles.tile_size)){
        globals.game_state.screen_center.x = globals.tiles.tile_w * globals.tiles.tile_size;
    }
    if (globals.game_state.screen_center.y < 0){
        globals.game_state.screen_center.y = 0;
    }
    if (globals.game_state.screen_center.y > (globals.tiles.tile_h * globals.tiles.tile_size)){
        globals.game_state.screen_center.y = globals.tiles.tile_h * globals.tiles.tile_size;
    }
}

void update_logic(void)
{
    keyboard_actions();
    mouse_actions();
    bound_screen();

    set_zoom_level();
    mouse_clear_diff();
}
