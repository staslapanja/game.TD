
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
    globals.mouse.grid_x = 0;
    globals.mouse.grid_y = 0;
    globals.mouse.tile_x = 0;
    globals.mouse.tile_y = 0;
    globals.mouse.dx = 0;
    globals.mouse.dy = 0;
    globals.mouse.tile_info = 0;
    globals.mouse.is_rail = false;
    globals.mouse.is_river = false;
    globals.mouse.is_struct = false;
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
    globals.game_state.side_menu_w = 200;
    //object pointers
    globals.enemy = NULL;
    globals.enemy_num = 0;
    globals.enemy_spawn = false;
    globals.towers = NULL;
    globals.buildings = NULL;
    globals.structures = NULL;
    globals.river = NULL;
    globals.rail = NULL;
    globals.rail_start.x = 0;
    globals.rail_start.y = 0;
    globals.rail_finish.x = 0;
    globals.rail_finish.y = 0;
    globals.place_object_active = false;
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

void init_structures(void)
{
    int w,h;
    w = globals.tiles.tile_w;
    h = globals.tiles.tile_h;
    //tile memory for objects being present
    globals.structures = (struct structures_t*)malloc(sizeof(struct structures_t) * w * h);

    //set all entries to NULL
    int i;
    for (i = 0; i < w * h; i++){
        globals.structures[i].t = NULL;
        globals.structures[i].b = NULL;
    }
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

void create_river(void)
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

void create_rail(void)
{
    int tile_w,tile_h;
    int x,y;
    tile_w = globals.tiles.tile_w;
    tile_h = globals.tiles.tile_h;
    globals.rail = (struct path_t*)malloc(sizeof(struct path_t) * tile_w * tile_h);
    int i,i_prev;
    //set all tiles as not set
    for(i=0; i < (globals.tiles.tile_w * globals.tiles.tile_h); i++){
        globals.rail[i].is_set = false;
    }

    //fixed rail configuration
    //start of rail
    x = 0;
    y = 1;
    globals.rail_start.x = x;
    globals.rail_start.y = y;
    i = y*tile_w+x;
    globals.rail[i].pos.x = x;
    globals.rail[i].pos.y = y;
    globals.rail[i].pos_prev.x = -1;
    globals.rail[i].pos_prev.y = -1;
    globals.rail[i].is_set = true;
    i_prev = i;
    int j;
    //go to right side - 1
    j = 1;
    while (j < globals.tiles.tile_w - 1){
        x = x + 1;
        y = y;
        i = y*tile_w+x;
        globals.rail[i].pos.x = x;
        globals.rail[i].pos.y = y;
        globals.rail[i].pos_prev = globals.rail[i_prev].pos;
        globals.rail[i_prev].pos_next = globals.rail[i].pos;
        globals.rail[i].is_set = true;
        j++;
        i_prev = i;
    }
    //go down to bottom -1
    j = y+1;
    while (j < globals.tiles.tile_h - 1){
        x = x;
        y = y + 1;
        i = y*tile_w+x;
        globals.rail[i].pos.x = x;
        globals.rail[i].pos.y = y;
        globals.rail[i].pos_prev = globals.rail[i_prev].pos;
        globals.rail[i_prev].pos_next = globals.rail[i].pos;
        globals.rail[i].is_set = true;
        j++;
        i_prev = i;
    }
    //go to left side
    j = x - 1;
    while (j >= 0){
        x = x - 1;
        y = y;
        i = y*tile_w+x;
        globals.rail[i].pos.x = x;
        globals.rail[i].pos.y = y;
        globals.rail[i].pos_prev = globals.rail[i_prev].pos;
        globals.rail[i_prev].pos_next = globals.rail[i].pos;
        globals.rail[i].is_set = true;
        j--;
        i_prev = i;
    }
    //set last one
    globals.rail[i].pos_next.x = -1;
    globals.rail[i].pos_next.y = -1;
    globals.rail_finish = globals.rail[i].pos;

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

        //check if item selected in menu with left click
        if (mouse_menu_check(x0+25,y0+25,x0+25+63,y0+25+63)){
            if (globals.mouse.lb == true){
                globals.game_state.tower0_place = true;
            }
        }

        //if left mouse button release
        if ((globals.game_state.tower0_place == true) ||
            (globals.game_state.house0_place == true) ||
            (globals.game_state.tower1_place == true) ||
            (globals.game_state.house1_place == true)){
            if (globals.mouse.lb == false){
                globals.place_object_active = true;
            }
        }

        if ((globals.place_object_active == true) && build_check()){
            if (globals.mouse.lb == true){
                //place object on map
                place_object_on_map();
                globals.place_object_active = false;
            }
        }
    } else {
        globals.game_state.tower0_place = false;
        globals.game_state.tower1_place = false;
        globals.game_state.house0_place = false;
        globals.game_state.house1_place = false;
        globals.place_object_active = false;
    }

    //reset building actions with right click
    if (globals.mouse.rb == true){
        globals.game_state.tower0_place = false;
        globals.game_state.tower1_place = false;
        globals.game_state.house0_place = false;
        globals.game_state.house1_place = false;
        globals.place_object_active = false;
    }

}

bool mouse_menu_check(float x0, float y0, float x1, float y1)
{
        if ((globals.mouse.x >= x0) &&
            (globals.mouse.x <= x1) &&
            (globals.mouse.y >= y0) &&
            (globals.mouse.y <= y1)){
                return true;
        }
        return false;
}

void mouse_to_grid(void)
{
    float x,y;
    float mouse_x,mouse_y;

    int tile_size;
    tile_size = globals.tiles.tile_size;

    //keep position inside screen
    if (globals.mouse.x > globals.game_state.screen_w){
        mouse_x = globals.game_state.screen_w;
    } else {
        mouse_x = globals.mouse.x;
    }
    if (globals.mouse.y > globals.game_state.screen_h){
        mouse_y = globals.game_state.screen_h;
    } else {
        mouse_y = globals.mouse.y;
    }
    //get mouse position on map
    x = globals.game_state.screen_center.x - globals.game_state.screen_w/2 + mouse_x;
    y = globals.game_state.screen_center.y - globals.game_state.screen_h/2 + mouse_y;

    //determine the position of the tile
    //that the mouse points to on the map
    if (x < 0){
        x = 0;
    } else if (x >= globals.tiles.tile_w * tile_size){
        x = (globals.tiles.tile_w-1);
    } else {
        x = (int)(x/tile_size);
    }

    globals.mouse.tile_x = x;
    x = x * tile_size;

    if (y < 0){
        y = 0;
    } else if (y >= globals.tiles.tile_h * tile_size){
        y = (globals.tiles.tile_h-1);
    } else {
        y = (int)(y/tile_size);
    }

    globals.mouse.tile_y = y;
    y = y * tile_size;

    //convert map position back to screen position
    globals.mouse.grid_x = x - (globals.game_state.screen_center.x - globals.game_state.screen_w/2);
    globals.mouse.grid_y = y - (globals.game_state.screen_center.y - globals.game_state.screen_h/2);
}

void get_cursor_info(void)
{
    int mouse_x,mouse_y;
    mouse_x = globals.mouse.tile_x;
    mouse_y = globals.mouse.tile_y;
    //get tile info
    globals.mouse.tile_info = globals.tiles.p[mouse_y*globals.tiles.tile_w+mouse_x];
    //check if on a rail
    globals.mouse.is_rail = globals.rail[mouse_y*globals.tiles.tile_w+mouse_x].is_set;
    //check if on a river
    //NOT YET SET!!!
    globals.mouse.is_river = false;
    globals.mouse.is_struct = false;
    if (globals.structures[mouse_y*globals.tiles.tile_w+mouse_x].t != NULL){
        globals.mouse.is_struct = true;
    }
    if (globals.structures[mouse_y*globals.tiles.tile_w+mouse_x].b != NULL){
        globals.mouse.is_struct = true;
    }
}

bool build_check(void)
{
    int tile_type;
    bool place_tower, place_house;

    place_tower = (globals.game_state.tower0_place == true) || (globals.game_state.tower1_place == true);
    place_house = (globals.game_state.house0_place == true) || (globals.game_state.house1_place == true);

    tile_type = globals.mouse.tile_info;

    if (globals.mouse.is_rail == true){
        return false;
    }

    if (globals.mouse.is_river == true){
        return false;
    }

    if (globals.mouse.is_struct == true){
        return false;
    }

    if (tile_type == TILE_BLANK){
            return false;
    }
    if (tile_type == TILE_LAND){
        if (place_house || place_tower){
            return true;
        } else {
            return false;
        }
    }
    if (tile_type == TILE_HILL){
        if (place_tower){
            return true;
        } else if (place_house){
            return false;
        } else {
            return false;
        }
    }
    if (tile_type == TILE_WATER){
            return false;
    }
    if (tile_type == TILE_GRASS){
        if (place_house || place_tower){
            return true;
        } else {
            return false;
        }
    }

    return false;
}

void place_object_on_map(void)
{
    int virtual_tile_size = 64;
    float x,y;
    x = globals.mouse.tile_x * virtual_tile_size;
    y = globals.mouse.tile_y * virtual_tile_size;
    if (globals.game_state.tower0_place == true){
        struct tower_t *temp = NULL;
        //int x, int y, float angle, float damage, int level, float range
        temp = create_tower(x, y, 0, 1, 1, 256);
        globals.towers = t_append_ll_item(globals.towers,temp);
        globals.structures[globals.mouse.tile_y * globals.tiles.tile_w + globals.mouse.tile_x].t = temp;
    }
    if (globals.game_state.house0_place == true){
        //
    }
    if (globals.game_state.tower1_place == true){
        //
    }
    if (globals.game_state.house1_place == true){
        //
    }
}

void set_zoom_tile_size(void)
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
    //create enemy
    if (globals.enemy_spawn == true) {
        struct enemy_t *temp = NULL;
        temp = create_enemy(globals.rail_start.x * 64, globals.rail_start.y * 64, 2, 100);
        globals.enemy = append_ll_item(globals.enemy,temp);
        globals.enemy_num++;
        globals.enemy_spawn = false;
    }
    //change position
    struct enemy_t *cursor = globals.enemy;
    while(cursor != NULL){
        //if enemy destroyed, remove it from all the target lists
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
        //move the enemy
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
    //always move towards the next path centre
    struct xy_t ppos, ppos_next;
    int path_num = a->path_num;
    float e_cx, e_cy;
    float pos_cx, pos_cy;
    ppos = globals.rail[path_num].pos;
    //if in finish tile do not update the position
    if ((globals.rail[path_num].pos_next.x != -1) && (globals.rail[path_num].pos_next.y != -1)){
        //enemy centre position
        e_cx = a->position.x + virtual_tile_size/2;
        e_cy = a->position.y + virtual_tile_size/2;
        //tile centre position
        pos_cx = ppos.x * virtual_tile_size + virtual_tile_size/2;
        pos_cy = ppos.y * virtual_tile_size + virtual_tile_size/2;
        ppos_next = globals.rail[path_num].pos_next;
        //if more than one tile from the current centre switch to next centre
        if ( ((abs(e_cx - pos_cx) >= virtual_tile_size)) || ((abs(e_cy - pos_cy) >= virtual_tile_size)) ){
            a->path_num = a->path_num + 1;
        }
        //move in x direction if next tile in x direction
        if ((ppos_next.x - ppos.x) > 0){
            a->position.x += a->speed;
        } else if ((ppos_next.x - ppos.x) < 0){
            a->position.x -= a->speed;
        }
        //move in y direction if next tile in y direction
        if ((ppos_next.y - ppos.y) > 0){
            a->position.y += a->speed;
        } else if ((ppos_next.y - ppos.y) < 0){
            a->position.y -= a->speed;
        }
    }
}

bool check_enemy_finish(struct enemy_t *a)
{
    int path_num = a->path_num;

    //check if finish tile
    if ((globals.rail[path_num].pos_next.x == -1) || (globals.rail[path_num].pos_next.y == -1)){
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

void init_logic(void)
{

    init_tiles(10,10);
    init_structures();

    create_map();
    //create_river();
    create_rail();

    move_screen(globals.tiles.map_center);

    //TEMP!!! for testing purposes
//    struct tower_t *temp = NULL;
//    temp = create_tower(64*2, 64*7, 0, 1, 1, 256);
//    globals.towers = t_append_ll_item(globals.towers,temp);
//    temp = create_tower(64*0, 64*7, 0, 1, 1, 256);
//    globals.towers = t_append_ll_item(globals.towers,temp);
//    temp = create_tower(64*5, 64*7, 0, 1, 1, 256);
//    globals.towers = t_append_ll_item(globals.towers,temp);
//    temp = create_tower(64*5, 64*9, 0, 1, 1, 256);
//    globals.towers = t_append_ll_item(globals.towers,temp);
}

void update_logic(void)
{
    keyboard_actions();
    mouse_actions();
    mouse_to_grid();
    get_cursor_info();
    bound_screen();

    set_zoom_tile_size();
    mouse_clear_diff();

    update_enemy();
    update_towers();
}
