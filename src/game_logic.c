
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
    globals.keys.key_d = false;
    globals.keys.key_c = false;
    globals.keys.key_t = false;
    //init mouse
    globals.mouse.lb = false;
    globals.mouse.rb = false;
    globals.mouse.x = 0;
    globals.mouse.y = 0;
    globals.mouse.map_x = 0;
    globals.mouse.map_y = 0;
    globals.mouse.grid_x = 0;
    globals.mouse.grid_y = 0;
    globals.mouse.tile_x = 0;
    globals.mouse.tile_y = 0;
    globals.mouse.dx = 0;
    globals.mouse.dy = 0;
    globals.mouse.tile_info = 0;
    globals.mouse.hill_info = 0;
    globals.mouse.is_rail = false;
    globals.mouse.is_river = false;
    globals.mouse.is_struct = false;
    //init game states
    globals.game_state.end_game = false;
    globals.game_state.grid_en = false;
    globals.game_state.side_menu_visible = true;
    globals.game_state.debug_on = false;
    globals.game_state.tower0_en = true;
    globals.game_state.tower0_place = false;
    globals.game_state.tower1_en = false;
    globals.game_state.tower1_place = false;
    globals.game_state.house0_en = false;
    globals.game_state.house0_place = false;
    globals.game_state.house1_en = false;
    globals.game_state.house1_place = false;
    globals.game_state.zoom_mult = 1.0f;
    globals.game_state.zoom_mult_old = 1.0f;
    globals.game_state.screen_center.x = 0;
    globals.game_state.screen_center.y = 0;
    globals.game_state.camera_pos.x = 0;
    globals.game_state.camera_pos.y = 0;
    globals.game_state.screen_step = 8;
    globals.game_state.screen_w = al_get_display_width(display);
    globals.game_state.screen_h = al_get_display_height(display);
    globals.game_state.side_menu_w = 200;
    globals.game_state.top_bar_h = 32;
    globals.game_state.bottom_bar_h = 32;
    globals.game_state.map_screen_w = globals.game_state.screen_w - globals.game_state.side_menu_w;
    globals.game_state.map_screen_h = globals.game_state.screen_h - globals.game_state.top_bar_h - globals.game_state.bottom_bar_h;
    globals.game_state.credits = 100;
    globals.game_state.energy_produced = 0;
    globals.game_state.energy_required = 0;
    globals.game_state.count_down = 10 * GAME_UPDATES_PER_SEC;
    //object pointers
    globals.enemy = NULL;       //linked list
    globals.trains = NULL;      //linked list
    globals.enemy_num = 0;
    globals.enemy_spawn = false;
    globals.train_length = 1;
    globals.train_level = 1;
    globals.train_spawn = false;
    globals.towers = NULL;      //linked list
    globals.tower_list = NULL;
    globals.buildings = NULL;
    globals.structures = NULL;  //map list
    globals.river = NULL;
    globals.rail = NULL;
    globals.rail_start.x = 0;
    globals.rail_start.y = 0;
    globals.rail_finish.x = 0;
    globals.rail_finish.y = 0;
    globals.float_text = NULL;
}

void init_tiles(int w, int h)
{
    //tile pointer memory
    globals.tiles.p = (int*)malloc(sizeof(int) * w * h);
    globals.tiles.hill = (int*)malloc(sizeof(int) * w * h);

    //set all entries to NULL
    int i;
    for (i = 0; i < w * h; i++){
        globals.tiles.p[i] = TILE_BLANK;
        globals.tiles.hill[i] = 0x0;
    }
    globals.tiles.tile_w = w;
    globals.tiles.tile_h = h;
    //set the map centre
    globals.tiles.map_center.x = (w * TILE_DEFSIZE)/2;
    globals.tiles.map_center.y = (h * TILE_DEFSIZE)/2;
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

void move_camera(float x, float y)
{
    globals.game_state.camera_pos.x = x;
    globals.game_state.camera_pos.y = y;
}

void zoom_to_camera_pos(float x, float y)
{
    //zoom while keeping x,y at the same position
    float t_x, t_y;
    float mult = globals.game_state.zoom_mult;
    float mult_old = globals.game_state.zoom_mult_old;

    t_x = globals.game_state.camera_pos.x + (x * (1/mult_old - 1/mult));
    t_y = globals.game_state.camera_pos.y + (y * (1/mult_old - 1/mult));

    move_camera(t_x,t_y);
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
    //////////////
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

    //ad rail IDs
    add_ids_to_rail(globals.rail,globals.rail_start,globals.rail_finish);

}

void add_ids_to_rail(struct path_t *rail, struct xy_t rail_start, struct xy_t rail_finish)
{
    //Add rail IDs to different shapes of the rail for drawing
    //and calculations
    //Assume that rails start and finish on the left side of the map

    int w,h,i;
    int w_prev,h_prev,w_next,h_next;
    int dw0, dw1, dh0, dh1;
    int tile_w;

    tile_w = globals.tiles.tile_w;

    //First rail will be starting from the side of the screen
    w = globals.rail_start.x;
    h = globals.rail_start.y;

    while ((w != -1) && (h != -1)){
        i = h * tile_w + w;
        //If start tile set virtual prev tile for correct tile selection
        if (globals.rail[i].pos_prev.x == -1){
            w_prev = w - 1; //Move one tile left
        } else {
            w_prev = globals.rail[i].pos_prev.x;
        }
        if (globals.rail[i].pos_prev.y == -1){
            h_prev = h; //Stay in same row
        } else {
            h_prev = globals.rail[i].pos_prev.y;
        }

        //If finish tile set virtual next tile for correct tile selection
        if (globals.rail[i].pos_next.x == -1){
            w_next = w - 1; //Move one tile left
        } else {
            w_next = globals.rail[i].pos_next.x;
        }
        if (globals.rail[i].pos_next.y == -1){
            h_next = h; //Stay in same row
        } else {
            h_next = globals.rail[i].pos_next.y;
        }

        dw0 = w - w_prev;
        dw1 = w_next - w;
        dh0 = h - h_prev;
        dh1 = h_next - h;
        //straight section in x direction
        if ((dw0 != 0) && (dw1 != 0)){
            globals.rail[i].id = TILE_ID_RAIL_0;
        }
        //straight section in y direction
        if ((dh0 != 0) && (dh1 != 0)){
            globals.rail[i].id = TILE_ID_RAIL_1;
        }
        //corner section
        //N-E
        if ((dw0 == 0) && (dw1 == 1) && (dh0 == 1) && (dh1 == 0)){
            globals.rail[i].id = TILE_ID_RAIL_3;
        }
        //N-W
        if ((dw0 == 0) && (dw1 == -1) && (dh0 == 1) && (dh1 == 0)){
            globals.rail[i].id = TILE_ID_RAIL_5;
        }
        //S-E
        if ((dw0 == 0) && (dw1 == 1) && (dh0 == -1) && (dh1 == 0)){
            globals.rail[i].id = TILE_ID_RAIL_2;
        }
        //W-S
        if ((dw0 == 1) && (dw1 == 0) && (dh0 == 0) && (dh1 == 1)){
            globals.rail[i].id = TILE_ID_RAIL_4;
        }
        //E-N
        if ((dw0 == -1) && (dw1 == 0) && (dh0 == 0) && (dh1 == -1)){
            globals.rail[i].id = TILE_ID_RAIL_3;
        }
        //E-S
        if ((dw0 == -1) && (dw1 == 0) && (dh0 == 0) && (dh1 == -1)){
            globals.rail[i].id = TILE_ID_RAIL_2;
        }
        //S-W
        if ((dw0 == 0) && (dw1 == -1) && (dh0 == -1) && (dh1 == 0)){
            globals.rail[i].id = TILE_ID_RAIL_4;
        }
        //W-N
        if ((dw0 == 1) && (dw1 == 0) && (dh0 == 0) && (dh1 == -1)){
            globals.rail[i].id = TILE_ID_RAIL_5;
        }

        //set next position variables
        w = w_next;
        h = h_next;
    }

}

void create_tower_list(void)
{
    globals.tower_list = (struct tower_list_t*)malloc(sizeof(struct tower_list_t));
    struct tower_t *temp;
    temp = create_tower(0, 0, 0, 1, 1, 256, 100);
    globals.tower_list->tower0 = temp;
    temp = create_tower(0, 0, 0, 5, 1, 384, 1000);
    globals.tower_list->tower1 = temp;
}

void keyboard_actions(void)
{
    //zoom control
    if (globals.keys.key_z == true){
        globals.game_state.zoom_mult_old = globals.game_state.zoom_mult;
        globals.game_state.zoom_mult = 1.0;
        globals.keys.key_z = false;
        zoom_to_camera_pos(globals.game_state.screen_w/2,
                           globals.game_state.screen_h/2);
    }

    float mult = globals.game_state.zoom_mult;

    //camera move with keys
    if (globals.keys.key_right == true)
        globals.game_state.camera_pos.x += globals.game_state.screen_step / mult;
    if (globals.keys.key_left == true)
        globals.game_state.camera_pos.x -= globals.game_state.screen_step / mult;
    if (globals.keys.key_down == true)
        globals.game_state.camera_pos.y += globals.game_state.screen_step / mult;
    if (globals.keys.key_up == true)
        globals.game_state.camera_pos.y -= globals.game_state.screen_step / mult;

    //Centre camera
    if (globals.keys.key_c == true){
        move_camera(globals.tiles.map_center.x-(globals.game_state.screen_w/2)/mult,
                    globals.tiles.map_center.y-(globals.game_state.screen_h/2)/mult);
        globals.keys.key_c = false;
    }

    //grid enable
    if (globals.keys.key_g == true){
        globals.game_state.grid_en = !globals.game_state.grid_en;
        globals.keys.key_g = false;
    }

    //side menu enable
    if (globals.keys.key_b == true){
        globals.game_state.side_menu_visible = !globals.game_state.side_menu_visible;
        globals.keys.key_b = false;
    }

    //spawn enemy
    if (globals.keys.key_e == true){
        globals.enemy_spawn = true;
        globals.keys.key_e = false;
    }

    //spawn train
    if (globals.keys.key_t == true){
        globals.train_spawn = true;
        globals.keys.key_t = false;
    }

    //debug_screen
    if (globals.keys.key_d == true){
        globals.game_state.debug_on = !globals.game_state.debug_on;
        globals.keys.key_d = false;
    }
}

void mouse_actions(void)
{

    //zoom control with mouse wheel
    if (globals.mouse.dz > 0){
        globals.game_state.zoom_mult_old = globals.game_state.zoom_mult;
        if (globals.game_state.zoom_mult < MAX_ZOOM){
            globals.game_state.zoom_mult *= 1.1;
        }
        zoom_to_camera_pos(globals.mouse.x,globals.mouse.y);
    } else if (globals.mouse.dz < 0){
        globals.game_state.zoom_mult_old = globals.game_state.zoom_mult;
        if (globals.game_state.zoom_mult > MIN_ZOOM){
            globals.game_state.zoom_mult /= 1.1;
        }
        zoom_to_camera_pos(globals.mouse.x,globals.mouse.y);
    }

    float mult = globals.game_state.zoom_mult;

    //camera move with mouse if RB held
    if (globals.mouse.rb == true){
        //horizontal movement
        globals.game_state.camera_pos.x -= globals.mouse.dx / mult;
        //vertical movement
        globals.game_state.camera_pos.y -= globals.mouse.dy / mult;
    }

    //menu actions
    if (globals.game_state.side_menu_visible == true){
        float x0,y0;
        int screen_w,top_bar;
        top_bar = globals.game_state.top_bar_h;
        screen_w = globals.game_state.screen_w;
        x0 = screen_w-globals.game_state.side_menu_w;
        y0 = 0;

        //check if item selected in menu with left click
        if (mouse_menu_check(x0+25,y0+25+top_bar,x0+25+63,y0+25+63+top_bar)){
            if (globals.mouse.lb == true){
                globals.game_state.tower0_place = true;
            }
        }

        if (place_check() && mouse_inside_map_screen() && price_check()){
            if (globals.mouse.lb == true){
                //place object on map
                place_object_on_map();
            }
        }
    } else {
        globals.game_state.tower0_place = false;
        globals.game_state.tower1_place = false;
        globals.game_state.house0_place = false;
        globals.game_state.house1_place = false;
    }

    //reset building actions with right click
    if (globals.mouse.rb == true){
        globals.game_state.tower0_place = false;
        globals.game_state.tower1_place = false;
        globals.game_state.house0_place = false;
        globals.game_state.house1_place = false;
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

bool mouse_inside_map_screen(void)
{
    int mouse_x, mouse_y;
    mouse_x = globals.mouse.x;
    mouse_y = globals.mouse.y;

    int screen_w, screen_h, top_bar_h, side_menu_w;
    screen_w = globals.game_state.screen_w;
    screen_h = globals.game_state.screen_h;
    top_bar_h = globals.game_state.top_bar_h;
    side_menu_w = globals.game_state.side_menu_w;

    bool check_x,check_y;
    check_x = (mouse_x >= 0) && (mouse_x < (screen_w - side_menu_w));
    check_y = (mouse_y >= top_bar_h) && (mouse_y < screen_h);

    if (check_x && check_y){
        return true;
    } else {
        return false;
    }
}

void mouse_to_grid(void)
{
    float x,y;
    float mouse_x,mouse_y;

    int tile_size;
    tile_size = TILE_DEFSIZE;
    float mult = globals.game_state.zoom_mult;

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
    x = globals.game_state.camera_pos.x + (mouse_x / mult);
    y = globals.game_state.camera_pos.y + (mouse_y / mult);

    globals.mouse.map_x = x;
    globals.mouse.map_y = y;

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

    if (y < 0){
        y = 0;
    } else if (y >= globals.tiles.tile_h * tile_size){
        y = (globals.tiles.tile_h-1);
    } else {
        y = (int)(y/tile_size);
    }

    globals.mouse.tile_y = y;

    //convert map position back to screen position
    //round tile size to integer
    globals.mouse.grid_x = (x * (int)(tile_size * mult)) - globals.game_state.camera_pos.x * mult;
    globals.mouse.grid_y = (y * (int)(tile_size * mult)) - globals.game_state.camera_pos.y * mult;
}

void get_cursor_info(void)
{
    int mouse_x,mouse_y;
    mouse_x = globals.mouse.tile_x;
    mouse_y = globals.mouse.tile_y;
    //get tile info
    globals.mouse.tile_info = globals.tiles.p[mouse_y*globals.tiles.tile_w+mouse_x];
    //get hill info
    globals.mouse.hill_info = globals.tiles.hill[mouse_y*globals.tiles.tile_w+mouse_x];
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

bool price_check(void)
{
    float credits = globals.game_state.credits;

    if (globals.game_state.tower0_place == true){
        if (credits >= globals.tower_list->tower0->price){
            return true;
        }
    }

    if (globals.game_state.tower1_place == true){
        if (credits >= globals.tower_list->tower1->price){
            return true;
        }
    }

    return false;
}

bool place_check(void)
{
    int tile_type, hill_type;
    bool place_tower, place_house;

    place_tower = (globals.game_state.tower0_place == true) || (globals.game_state.tower1_place == true);
    place_house = (globals.game_state.house0_place == true) || (globals.game_state.house1_place == true);

    tile_type = globals.mouse.tile_info;
    hill_type = globals.mouse.hill_info;

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
    if (hill_type){
        if (place_tower){
            return false;
        } else if (place_house){
            return false;
        } else {
            return false;
        }
    }
    if (tile_type == TILE_LAND){
        if (place_house || place_tower){
            return true;
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
        temp = create_tower(0, 0, 0, 0, 0, 0, 0);
        //copy tower template to newly allocated memory
        memcpy(temp, globals.tower_list->tower0, sizeof (struct tower_t));
        temp->position.x = x;
        temp->position.y = y;
        globals.towers = append_ll_item(globals.towers,temp);
        globals.structures[globals.mouse.tile_y * globals.tiles.tile_w + globals.mouse.tile_x].t = temp;
        //subtract credits and add a floating text
        globals.game_state.credits = globals.game_state.credits - temp->price;
        char text_holder[20];
        struct float_text_t *temp_ft;
        sprintf(text_holder, "-$%d",temp->price);
        ALLEGRO_COLOR text_color = al_map_rgb(255,69,0); //orange red
        temp_ft = create_float_text(x, y, 1, 60, text_holder, text_color);
        globals.float_text = append_ll_item(globals.float_text,temp_ft);
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

void mouse_clear_diff(void)
{
    globals.mouse.dx = 0;
    globals.mouse.dy = 0;
    globals.mouse.dz = 0;
}

void bound_screen_inside_virtual_map(void)
{
    float tile_size = TILE_DEFSIZE;
    int tile_w = globals.tiles.tile_w;
    int tile_h = globals.tiles.tile_h;
    int screen_w = globals.game_state.screen_w;
    int screen_h = globals.game_state.screen_h;
    float mult = globals.game_state.zoom_mult;

    //correct if screen is out of bounds
    if (globals.game_state.camera_pos.x < -(screen_w/2)/mult){
        globals.game_state.camera_pos.x = -(screen_w/2)/mult;
    }
    if (globals.game_state.camera_pos.x > (tile_w * tile_size)-(screen_w/2)/mult){
        globals.game_state.camera_pos.x = (tile_w * tile_size)-(screen_w/2)/mult;
    }
    if (globals.game_state.camera_pos.y < -(screen_h/2)/mult){
        globals.game_state.camera_pos.y = -(screen_h/2)/mult;
    }
    if (globals.game_state.camera_pos.y > (tile_h * tile_size)-(screen_h/2)/mult){
        globals.game_state.camera_pos.y = (tile_h * tile_size)-(screen_h/2)/mult;
    }
}

void update_enemy(void)
{
    int tile_w = globals.tiles.tile_w;
    //create enemy
    if ((globals.enemy_spawn == true) || (globals.game_state.count_down <= 0)){
        struct enemy_t *temp = NULL;
        temp = create_enemy(globals.rail_start.x * TILE_DEFSIZE, globals.rail_start.y * TILE_DEFSIZE, globals.rail_start.y * tile_w + globals.rail_start.x, 2, 100,10);
        globals.enemy = append_ll_item(globals.enemy,temp);
        globals.enemy_num++;
        globals.enemy_spawn = false;
        globals.game_state.count_down = 10 * GAME_UPDATES_PER_SEC;
    }
    //change position
    struct llist_t *cursor = globals.enemy;
    struct enemy_t *enemy;
    while(cursor != NULL){
        enemy = cursor->ptr;
        //if enemy destroyed, remove it from all the target lists
        if (enemy->health <= 0){
            //remove from tower list
            struct llist_t *t_cursor = globals.towers;
            struct tower_t *tower;
            while(t_cursor != NULL){
                tower = t_cursor->ptr;
                if (tower->e_target == enemy){
                    tower->e_target = NULL;
                }
                t_cursor = t_cursor->next;
            }
            //add floating text for credits reward and update credits
            char text_holder[20];
            struct float_text_t *temp_ft;
            sprintf(text_holder, "$%d",enemy->credits);
            ALLEGRO_COLOR text_color = al_map_rgb(218,165,32); //golden rod
            temp_ft = create_float_text(enemy->position.x, enemy->position.y, 1, 60, text_holder, text_color);
            globals.float_text = append_ll_item(globals.float_text,temp_ft);
            globals.game_state.credits += enemy->credits;
            //remove enemy
            struct llist_t *temp = cursor;
            cursor = cursor->next;
            globals.enemy = remove_ll_item(globals.enemy,temp,free_enemy_t);
            globals.enemy_num--;
        //move the enemy
        } else {
            update_enemy_path(enemy);
            if(check_enemy_finish(enemy)){
                struct llist_t *temp = cursor;
                cursor = cursor->next;
                globals.enemy = remove_ll_item(globals.enemy,temp,free_enemy_t);
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
    int tile_w = globals.tiles.tile_w;
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
            a->path_num = ppos_next.y * tile_w + ppos_next.x;
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

void update_train(void)
{
    struct llist_t *cursor = globals.trains;
    struct train_t *train;
    int tile_w = globals.tiles.tile_w;
    struct train_t *temp = NULL;
    int start_rail = globals.rail_start.y * tile_w + globals.rail_start.x;
    bool start_slot_empty = true;

    //create new train
    if ((globals.train_spawn == true) || (globals.game_state.count_down <= 0)){
        //if any train part on start position, hold with spawn
        while(cursor != NULL){
            train = cursor->ptr;
            if (train->path_num == start_rail){
                start_slot_empty = false;
                cursor = NULL; //stop searching
            } else {
                cursor = cursor->next;
            }
        }
        //if start rail free, spawn new train composition
        if (start_slot_empty){
            temp = create_train_unit(1, globals.rail_start.x * TILE_DEFSIZE, globals.rail_start.y * TILE_DEFSIZE, globals.rail_start.y * tile_w + globals.rail_start.x, 1, 0, 2, 100,10);
            globals.trains = append_ll_item(globals.trains,temp);
            globals.train_spawn = false;
            globals.game_state.count_down = 10 * GAME_UPDATES_PER_SEC;
        }
    }
    //change position
    cursor = globals.trains;
    while(cursor != NULL){
        train = cursor->ptr;
        //if train destroyed, remove it from all the target lists
        if (train->health <= 0){
            //remove from tower list
            struct llist_t *t_cursor = globals.towers;
            struct tower_t *tower;
            while(t_cursor != NULL){
                tower = t_cursor->ptr;
                if (tower->t_target == train){
                    tower->t_target = NULL;
                }
                t_cursor = t_cursor->next;
            }
            //add floating text for credits reward and update credits
            char text_holder[20];
            struct float_text_t *temp_ft;
            sprintf(text_holder, "$%d",train->credits);
            ALLEGRO_COLOR text_color = al_map_rgb(218,165,32); //golden rod
            temp_ft = create_float_text(train->position.x, train->position.y, 1, 60, text_holder, text_color);
            globals.float_text = append_ll_item(globals.float_text,temp_ft);
            globals.game_state.credits += train->credits;
            //remove train
            struct llist_t *temp = cursor;
            cursor = cursor->next;
            globals.trains = remove_ll_item(globals.trains,temp,free_enemy_t);
        //move the train
        } else {
            update_train_path(train);
            if(check_train_finish(train)){
                struct llist_t *temp = cursor;
                cursor = cursor->next;
                globals.trains = remove_ll_item(globals.trains,temp,free_enemy_t);
            } else {
                cursor = cursor->next;
            }
        }
    }
}

void update_train_path(struct train_t *a)
{

    int virtual_tile_size;
    int path_num;
    float step;
    float tile_end_distance;
    float pos_x, pos_y;
    float pos_next_x, pos_next_y;
    bool rail_curve;

    virtual_tile_size = TILE_DEFSIZE;

    path_num = a->path_num;
    pos_x = globals.rail[path_num].pos.x;
    pos_y = globals.rail[path_num].pos.y;
    pos_next_x = globals.rail[path_num].pos_next.x;
    pos_next_y = globals.rail[path_num].pos_next.y;
    step = a->speed;
    globals.rail[path_num].

    //if in finish tile do not update the position
    if ((pos_next_x != -1) && (pos_next_y != -1)){

        //determine if straight or curved section
        //straight rail sections are 64 pixels long and curved are 47 pixels long (3 + 41 + 3)
        if (globals.rail[path_num].id & (TILE_ID_RAIL_0 | TILE_ID_RAIL_1)){
            rail_curve = 0;
        } else {
            rail_curve = 1;
        }

        while (step > 0){

            //distance left to on current tile
            tile_end_distance =

        }
    }
}

bool check_train_finish(struct train_t *a)
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
    struct llist_t *t_cursor = globals.towers;
    struct tower_t *tower;
    struct llist_t *tr_cursor;
    struct enemy_t *enemy;
    struct train_t *train;
    float t_x,t_y,tr_x,tr_y,dx,dy;

    while(t_cursor != NULL){
        tower = t_cursor->ptr;
        t_x = tower->position.x;
        t_y = tower->position.y;
        //if no target, clear fire active
        if ((tower->e_target == NULL) ||(tower->t_target == NULL)){
            tower->fire_active = false;
        }
        //check all enemies
        tr_cursor = globals.enemy;
        while(tr_cursor != NULL){
            enemy = tr_cursor->ptr;
            tr_x = enemy->position.x;
            tr_y = enemy->position.y;
            dx = tr_x-t_x;
            dy = tr_y-t_y;
            if ((sqrt(dx*dx + dy*dy)) <= tower->range){
                tower->e_target = enemy;
                tower->fire_active = true;
                //calculate as if 0 is north
                if (dy == 0){
                    tower->angle = (dx/abs(dx)) * ALLEGRO_PI/2;
                } else {
                    if (dy < 0){
                        tower->angle = atan(dx/abs(dy));
                    } else {
                        //if dx < 0 the rotation is PI + atan = - (PI - atan)
                        tower->angle = ALLEGRO_PI - atan(dx/abs(dy));
                    }

                }
                enemy->health -= tower->damage;
                tr_cursor = NULL;
            } else {
                tower->fire_active = false;
                tower->e_target = NULL;
                tr_cursor = tr_cursor->next;
            }
        }
        //check all trains
        tr_cursor = globals.trains;
        while(tr_cursor != NULL){
            train = tr_cursor->ptr;
            tr_x = train->position.x;
            tr_y = train->position.y;
            dx = tr_x-t_x;
            dy = tr_y-t_y;
            if ((sqrt(dx*dx + dy*dy)) <= tower->range){
                tower->t_target = train;
                tower->fire_active = true;
                //calculate as if 0 is north
                if (dy == 0){
                    tower->angle = (dx/abs(dx)) * ALLEGRO_PI/2;
                } else {
                    if (dy < 0){
                        tower->angle = atan(dx/abs(dy));
                    } else {
                        //if dx < 0 the rotation is PI + atan = - (PI - atan)
                        tower->angle = ALLEGRO_PI - atan(dx/abs(dy));
                    }

                }
                enemy->health -= tower->damage;
                tr_cursor = NULL;
            } else {
                tower->fire_active = false;
                tower->t_target = NULL;
                tr_cursor = tr_cursor->next;
            }
        }
        t_cursor = t_cursor->next;
    }
}

void update_float_text(void)
{
    struct llist_t *cursor = globals.float_text;
    struct float_text_t *float_text;
    while(cursor != NULL){
        float_text = cursor->ptr;
        if (float_text->timeout <= 0){
            struct llist_t *temp = cursor;
            globals.float_text = remove_ll_item(globals.float_text,temp,free_float_text_t);
        } else {
            float_text->y = float_text->y - float_text->move_per_tick;
            float_text->timeout = float_text->timeout - 1;
        }
        cursor = cursor->next;
    }
}

void update_timers(void)
{
    globals.game_state.count_down -= 1;
}

void init_logic(void)
{

    init_tiles(16,16);
    init_structures();

    generate_map();
    //create_river();
    create_rail();

    create_tower_list();

    move_camera(globals.tiles.map_center.x-globals.game_state.map_screen_w/2,globals.tiles.map_center.y-globals.game_state.screen_h/2);

}

void update_logic(void)
{
    keyboard_actions();
    mouse_actions();
    update_timers();
    mouse_to_grid();
    get_cursor_info();
    bound_screen_inside_virtual_map();

    mouse_clear_diff();

//    update_enemy();
    update_train();
    update_towers();
    update_float_text();
}

