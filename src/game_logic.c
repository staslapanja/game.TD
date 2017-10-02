
#include "game_logic.h"

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
    globals.game_state.tower0_place = false;
    globals.game_state.tower1_en = false;
    globals.game_state.tower1_place = false;
    globals.game_state.house0_en = false;
    globals.game_state.house0_place = false;
    globals.game_state.house1_en = false;
    globals.game_state.house1_place = false;
    globals.game_state.zoom = 1;
    globals.game_state.screen_center.x = 0;
    globals.game_state.screen_center.y = 0;
    globals.game_state.screen_step = 8;
    globals.game_state.screen_w = al_get_display_width(display);
    globals.game_state.screen_h = al_get_display_height(display);
    globals.game_state.side_menu_w = 182;
    //object pointers
    globals.enemy = NULL;
    globals.enemy_num = 0;
    globals.enemy_spawn = false;
    globals.towers = NULL;
    globals.buildings = NULL;
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
            sel = ((rand()%3) > 0) ? TILE_LAND : TILE_HILL;
            globals.tiles.p[h*globals.tiles.tile_w + w] = sel;
        }
    }
}

void add_river(void)
{
    int h,w;

    for (h = 0; h < globals.tiles.tile_h; h++){
        for (w = 0; w < globals.tiles.tile_w; w++){
            if (((w == 1) || (w == globals.tiles.tile_w - 2)) && (h < globals.tiles.tile_h - 1)){
                globals.tiles.p[h*globals.tiles.tile_w + w] = TILE_WATER;
            } else if ((w > 1) && (w < globals.tiles.tile_w - 2) && (h == globals.tiles.tile_h - 2)){
                globals.tiles.p[h*globals.tiles.tile_w + w] = TILE_WATER;
            }
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

    //spawn enemy
    if (globals.keys.key_e == true){
        globals.enemy_spawn = true;
        globals.keys.key_e = false;
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

    //menu actions
    if (globals.game_state.build_menu_on == true){
        float x0,y0;
        int screen_w;
        screen_w = al_get_display_width(display);
        x0 = screen_w-globals.game_state.side_menu_w;
        y0 = 0;

        if ((globals.mouse.x >= x0+19) &&
            (globals.mouse.x <= x0+19+63) &&
            (globals.mouse.y >= y0+19) &&
            (globals.mouse.y <= y0+19+63)){
                if (globals.mouse.lb == true){
                    globals.game_state.tower0_place = true;
                }
            }
    }

    //reset building actions with right click
    if (globals.mouse.rb == true){
        globals.game_state.tower0_place = false;
        globals.game_state.tower1_place = false;
        globals.game_state.house0_place = false;
        globals.game_state.house1_place = false;
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

void update_enemy(void)
{
    //create enemy if less than max
    if (globals.enemy_spawn == true) {
        struct enemy_t *temp = NULL;
        temp = create_enemy(64, 0, 2, 100);
        globals.enemy = append_ll_item(globals.enemy,temp);
        globals.enemy_num++;
        globals.enemy_spawn = false;
    }
    //change position
    struct enemy_t *cursor = globals.enemy;
    while(cursor != NULL){
        if (cursor->health <= 0){
            //remove from tower list
            struct tower_t *t_cursor = globals.towers;
            while(t_cursor != NULL){
                if (t_cursor->target == cursor){
                    t_cursor->target = NULL;
                }
                t_cursor = t_cursor->next;
            }
            //remove enemy
            struct enemy_t *temp = cursor;
            cursor = cursor->next;
            globals.enemy = remove_ll_item(globals.enemy,temp);
            globals.enemy_num--;
        } else {
            update_enemy_path(cursor);
            if(check_enemy_finish(cursor)){
                struct enemy_t *temp = cursor;
                cursor = cursor->next;
                globals.enemy = remove_ll_item(globals.enemy,temp);
                globals.enemy_num--;
            } else {
                cursor = cursor->next;
            }
        }
    }
}

void update_enemy_path(struct enemy_t *a)
{
    int virtual_tile_size = 64;

    if ((a->position.x == virtual_tile_size) && (a->position.y < (globals.tiles.tile_h-2) * virtual_tile_size)){
        a->position.y += a->speed;
    } else if ((a->position.x < (globals.tiles.tile_w-2) * virtual_tile_size) && (a->position.y >= (globals.tiles.tile_h-2) * virtual_tile_size)){
        a->position.x += a->speed;
        a->position.y = (globals.tiles.tile_h-2) * virtual_tile_size;
    } else if (a->position.x >= (globals.tiles.tile_w-2) * virtual_tile_size){
        a->position.x = (globals.tiles.tile_w-2) * virtual_tile_size;
        a->position.y -= a->speed;
    }
}

bool check_enemy_finish(struct enemy_t *a)
{
    int virtual_tile_size = 64;
    if ((a->position.x >= (globals.tiles.tile_w-2) * virtual_tile_size) && (a->position.y <= 0)){
            return true;
    }
    return false;
}

void update_towers(void)
{
    //seek nearest enemy in range
    struct tower_t *t_cursor = globals.towers;
    struct enemy_t *e_cursor;
    float t_x,t_y,e_x,e_y,dx,dy;

    while(t_cursor != NULL){
        t_x = t_cursor->position.x;
        t_y = t_cursor->position.y;
        //if no target, clear fire active
        if (t_cursor->target == NULL){
            t_cursor->fire_active = false;
        }
        //check all enemies
        e_cursor = globals.enemy;
        while(e_cursor != NULL){
            e_x = e_cursor->position.x;
            e_y = e_cursor->position.y;
            dx = e_x-t_x;
            dy = e_y-t_y;
            if ((sqrt(dx*dx + dy*dy)) <= t_cursor->range){
                t_cursor->target = e_cursor;
                t_cursor->fire_active = true;
                //calculate as if 0 is north
                if (dy == 0){
                    t_cursor->angle = (dx/abs(dx)) * ALLEGRO_PI/2;
                } else {
                    if (dy < 0){
                        t_cursor->angle = atan(dx/abs(dy));
                    } else {
                        //if dx < 0 the rotation is PI + atan = - (PI - atan)
                        t_cursor->angle = ALLEGRO_PI - atan(dx/abs(dy));
                    }

                }
                e_cursor->health -= t_cursor->damage;
                e_cursor = NULL;
            } else {
                t_cursor->fire_active = false;
                t_cursor->target = NULL;
                e_cursor = e_cursor->next;
            }
        }
        t_cursor = t_cursor->next;
    }
}

void update_logic(void)
{
    keyboard_actions();
    mouse_actions();
    bound_screen();

    set_zoom_level();
    mouse_clear_diff();

    update_enemy();
    update_towers();
}
