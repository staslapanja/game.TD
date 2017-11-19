
#include "draw_graphics.h"

void create_tiles(void)
{

    //TILE_BLANK 0
    globals.tiles.tile[TILE_BLANK] = al_create_bitmap(64, 64);
    al_set_target_bitmap(globals.tiles.tile[TILE_BLANK]);
    al_clear_to_color(al_map_rgb(0, 0, 0));

    //TILE_LAND  1
    globals.tiles.tile[TILE_LAND] = al_load_bitmap("resources/desert_tile.png");

    if (globals.tiles.tile[TILE_LAND] == NULL) //fallback graphic
    {
        globals.tiles.tile[TILE_LAND] = al_create_bitmap(64, 64);
        al_set_target_bitmap(globals.tiles.tile[TILE_LAND]);
        al_clear_to_color(al_map_rgba(205, 133, 63, 255));
    }

    //TILE_HILL  2
    globals.tiles.tile[TILE_HILL] = al_load_bitmap("resources/hill_atlas.png");
    if (globals.tiles.tile[TILE_LAND] == NULL) //fallback graphic
    {
        abort_game("Resource hill_atlas.png not loaded!");
    }
    //TILE_WATER 3
    globals.tiles.tile[TILE_WATER] = al_create_bitmap(64, 64);
    al_set_target_bitmap(globals.tiles.tile[TILE_WATER]);
    al_clear_to_color(al_map_rgba(135, 206, 250, 255));
    //TILE_GRASS 4
    globals.tiles.tile[TILE_GRASS] = al_create_bitmap(64, 64);
    al_set_target_bitmap(globals.tiles.tile[TILE_GRASS]);
    al_clear_to_color(al_map_rgba(50, 205, 50, 255));

    //TILE_RAIL_STRAIGHT  5
    globals.tiles.tile[TILE_RAIL_STRAIGHT] = al_load_bitmap("resources/rail_straight.png");
    if (globals.tiles.tile[TILE_RAIL_STRAIGHT] == NULL) //fallback graphic
    {
        globals.tiles.tile[TILE_RAIL_STRAIGHT] = al_create_bitmap(64, 64);
        al_set_target_bitmap(globals.tiles.tile[TILE_RAIL_STRAIGHT]);
        al_draw_filled_rectangle(16, 0, 48, 64, al_map_rgb(105,105,105));//dim gray / dim grey
        al_draw_filled_rectangle(30, 0, 34, 64, al_map_rgb(75,0,130));//indigo
    }

    //TILE_RAIL_CORNER    6
    globals.tiles.tile[TILE_RAIL_CORNER] = al_load_bitmap("resources/rail_corner.png");
    if (globals.tiles.tile[TILE_RAIL_CORNER] == NULL) //fallback graphic
    {
        globals.tiles.tile[TILE_RAIL_CORNER] = al_create_bitmap(64, 64);
        al_set_target_bitmap(globals.tiles.tile[TILE_RAIL_CORNER]);
        al_draw_filled_rectangle(16, 0, 48, 48, al_map_rgb(105,105,105));//dim gray / dim grey
        al_draw_filled_rectangle(48, 16,64, 48, al_map_rgb(105,105,105));//dim gray / dim grey
        al_draw_filled_rectangle(30, 0, 34, 34, al_map_rgb(75,0,130));//indigo
        al_draw_filled_rectangle(34,30, 64, 34, al_map_rgb(75,0,130));//indigo
    }

    //reselect the display buffer
    al_set_target_backbuffer(display);


}

void create_game_objects(void)
{
    //OBJ_ENEMY
    globals.objects[OBJ_ENEMY] = al_load_bitmap("resources/enemy.png");
    if (globals.objects[OBJ_ENEMY] == NULL) //fallback graphic
    {
        globals.objects[OBJ_ENEMY] = al_create_bitmap(64, 64);
        al_set_target_bitmap(globals.objects[OBJ_ENEMY]);
        al_draw_filled_circle(32, 32, 16, al_map_rgba(127, 0, 127, 255));
    }
    //OBJ_TOWER
    globals.objects[OBJ_TOWER]  = al_load_bitmap("resources/tower_base.png");
    if (globals.objects[OBJ_TOWER]  == NULL) //fallback graphic
    {
        globals.objects[OBJ_TOWER] = al_create_bitmap(64, 64);
        al_set_target_bitmap(globals.objects[OBJ_TOWER]);
        al_draw_filled_rectangle(8, 8, 56, 56, al_map_rgba(119,136,153, 255));
    }
    //OBJ_TOWER_GUN
    globals.objects[OBJ_TOWER_GUN]  = al_load_bitmap("resources/tower_gun.png");
    if (globals.objects[OBJ_TOWER_GUN]  == NULL) //fallback graphic
    {
        globals.objects[OBJ_TOWER_GUN] = al_create_bitmap(64, 64);
        al_set_target_bitmap(globals.objects[OBJ_TOWER_GUN]);
        al_draw_filled_circle(32, 32, 16, al_map_rgba(176,196,222, 255));
        al_draw_line(32, 32, 32, 0, al_map_rgb(0, 0, 0), 4);
    }

    //reselect the display buffer
    al_set_target_backbuffer(display);
}

void create_ui_items(void)
{
    //UI_BUILD_OK
    globals.ui_items[UI_BUILD_OK]  = al_load_bitmap("resources/build_ok.png");
    if (globals.ui_items[UI_BUILD_OK]  == NULL) //fallback graphic
    {
        globals.ui_items[UI_BUILD_OK] = al_create_bitmap(64, 64);
        al_set_target_bitmap(globals.ui_items[UI_BUILD_OK]);
        al_draw_filled_circle(32, 32, 16, al_map_rgba(0,255, 0, 255));
    }

    //UI_BUILD_BAD
    globals.ui_items[UI_BUILD_BAD]  = al_load_bitmap("resources/build_bad.png");
    if (globals.ui_items[UI_BUILD_BAD]  == NULL) //fallback graphic
    {
        globals.ui_items[UI_BUILD_BAD] = al_create_bitmap(64, 64);
        al_set_target_bitmap(globals.ui_items[UI_BUILD_BAD]);
        al_draw_filled_circle(32, 32, 16, al_map_rgba(255, 0, 0, 255));
    }

    //UI_TWR_RANGE
    globals.ui_items[UI_TWR_RANGE] = al_load_bitmap("resources/range_ring.png");
    if (globals.ui_items[UI_TWR_RANGE] == NULL) //fallback graphic
    {
        globals.ui_items[UI_TWR_RANGE] = al_create_bitmap(128, 128);
        al_set_target_bitmap(globals.ui_items[UI_TWR_RANGE]);
        al_draw_filled_circle(64, 64, 64, al_map_rgba(0,50,50, 16));
    }

    //reselect the display buffer
    al_set_target_backbuffer(display);
}

void init_graphics(void)
{
    create_tiles();
    create_game_objects();
    create_ui_items();
}

void update_graphics(void)
{
    draw_background();
    draw_map();
    draw_rail();
    draw_enemy();
    draw_towers();
    draw_floating_text();
    draw_cursor_rect();
    draw_build_menu();
    draw_top_bar();
}

void draw_background(void)
{
    //black background
    al_clear_to_color(al_map_rgb(0, 0, 0)); //black background
}

void draw_map(void)
{

    int w,h;
    int tile_type, hill_type;
    float x,y;

    int tile_size;

    float offset = 0.5f; //define pixels in the center of a pixel area
    ALLEGRO_COLOR grid_color = al_map_rgb(0, 0, 0);  //black

    tile_size = globals.tiles.tile_size;

    for (h = 0; h < globals.tiles.tile_h; h++){
        for (w = 0; w < globals.tiles.tile_w; w++){

            x = globals.game_state.screen_w/2 - globals.game_state.screen_center.x + w * tile_size;
            y = globals.game_state.screen_h/2 - globals.game_state.screen_center.y + h * tile_size;

            //check to only draw the visible tiles instead of the whole map
            //change to calculation to remove unneeded checks!!!
            if ((x > -tile_size) && (x < globals.game_state.screen_w + tile_size) && (y > -tile_size) && (y < globals.game_state.screen_h + tile_size)){
                tile_type = globals.tiles.p[h*globals.tiles.tile_w+w];
                hill_type = globals.tiles.hill[h*globals.tiles.tile_w+w];
                if (tile_type == TILE_BLANK){
                    al_draw_scaled_bitmap(globals.tiles.tile[TILE_BLANK], 0, 0, 64, 64, x , y , tile_size, tile_size,  0x0);
                }
                if (tile_type == TILE_LAND){
                    al_draw_scaled_bitmap(globals.tiles.tile[TILE_LAND], 0, 0, 64, 64, x , y , tile_size, tile_size, 0x0);
                }
                if (hill_type){
                    draw_hill(x, y, hill_type, tile_size);
                }
                if (tile_type == TILE_WATER){
                    al_draw_scaled_bitmap(globals.tiles.tile[TILE_WATER], 0, 0, 64, 64, x , y , tile_size, tile_size, 0x0);
                }
                if (tile_type == TILE_GRASS){
                    al_draw_scaled_bitmap(globals.tiles.tile[TILE_GRASS], 0, 0, 64, 64, x , y , tile_size, tile_size, 0x0);
                }
                //draw grid around the tile if enabled
                if (globals.game_state.grid_en == true){
                    al_draw_rectangle(x + offset,y + offset, x + tile_size-1 + offset,y + tile_size-1 + offset, grid_color, 1);
                }
            }
        }
    }

}

void draw_hill(float x, float y, int hill_type, int tile_size)
{

    if (hill_type & TILE_ID_HILL_0){
        al_draw_scaled_bitmap(globals.tiles.tile[TILE_HILL], 0 * 64, 0 * 64, 64, 64, x , y , tile_size, tile_size, 0x0);
    }
    if (hill_type & TILE_ID_HILL_1){
        al_draw_scaled_bitmap(globals.tiles.tile[TILE_HILL], 1 * 64, 0 * 64, 64, 64, x , y , tile_size, tile_size, 0x0);
    }
    if (hill_type & TILE_ID_HILL_2){
        al_draw_scaled_bitmap(globals.tiles.tile[TILE_HILL], 2 * 64, 0 * 64, 64, 64, x , y , tile_size, tile_size, 0x0);
    }
    if (hill_type & TILE_ID_HILL_3){
        al_draw_scaled_bitmap(globals.tiles.tile[TILE_HILL], 3 * 64, 0 * 64, 64, 64, x , y , tile_size, tile_size, 0x0);
    }
    if (hill_type & TILE_ID_HILL_4){
        al_draw_scaled_bitmap(globals.tiles.tile[TILE_HILL], 4 * 64, 0 * 64, 64, 64, x , y , tile_size, tile_size, 0x0);
    }
    if (hill_type & TILE_ID_HILL_5){
        al_draw_scaled_bitmap(globals.tiles.tile[TILE_HILL], 5 * 64, 0 * 64, 64, 64, x , y , tile_size, tile_size, 0x0);
    }
    if (hill_type & TILE_ID_HILL_6){
        al_draw_scaled_bitmap(globals.tiles.tile[TILE_HILL], 0 * 64, 1 * 64, 64, 64, x , y , tile_size, tile_size, 0x0);
    }
    if (hill_type & TILE_ID_HILL_7){
        al_draw_scaled_bitmap(globals.tiles.tile[TILE_HILL], 1 * 64, 1 * 64, 64, 64, x , y , tile_size, tile_size, 0x0);
    }
    if (hill_type & TILE_ID_HILL_8){
        al_draw_scaled_bitmap(globals.tiles.tile[TILE_HILL], 2 * 64, 1 * 64, 64, 64, x , y , tile_size, tile_size, 0x0);
    }
    if (hill_type & TILE_ID_HILL_8){
        al_draw_scaled_bitmap(globals.tiles.tile[TILE_HILL], 3 * 64, 1 * 64, 64, 64, x , y , tile_size, tile_size, 0x0);
    }
    if (hill_type & TILE_ID_HILL_9){
        al_draw_scaled_bitmap(globals.tiles.tile[TILE_HILL], 4 * 64, 1 * 64, 64, 64, x , y , tile_size, tile_size, 0x0);
    }
    if (hill_type & TILE_ID_HILL_10){
        al_draw_scaled_bitmap(globals.tiles.tile[TILE_HILL], 5 * 64, 1 * 64, 64, 64, x , y , tile_size, tile_size, 0x0);
    }
    if (hill_type & TILE_ID_HILL_11){
        al_draw_scaled_bitmap(globals.tiles.tile[TILE_HILL], 0 * 64, 2 * 64, 64, 64, x , y , tile_size, tile_size, 0x0);
    }
    if (hill_type & TILE_ID_HILL_12){
        al_draw_scaled_bitmap(globals.tiles.tile[TILE_HILL], 1 * 64, 2 * 64, 64, 64, x , y , tile_size, tile_size, 0x0);
    }
    if (hill_type & TILE_ID_HILL_13){
        al_draw_scaled_bitmap(globals.tiles.tile[TILE_HILL], 2 * 64, 2 * 64, 64, 64, x , y , tile_size, tile_size, 0x0);
    }
    if (hill_type & TILE_ID_HILL_14){
        al_draw_scaled_bitmap(globals.tiles.tile[TILE_HILL], 3 * 64, 2 * 64, 64, 64, x , y , tile_size, tile_size, 0x0);
    }
    if (hill_type & TILE_ID_HILL_15){
        al_draw_scaled_bitmap(globals.tiles.tile[TILE_HILL], 4 * 64, 2 * 64, 64, 64, x , y , tile_size, tile_size, 0x0);
    }
}

void draw_rail(void)
{
    int w,h,i;
    int w_prev,h_prev,w_next,h_next;
    int dw0, dw1, dh0, dh1;
    float x,y;
    int tile_size,tile_w;
    float mult;

    tile_w = globals.tiles.tile_w;
    tile_size = globals.tiles.tile_size;
    mult = (float)tile_size/64;

    i = globals.rail_start.y * tile_w + globals.rail_start.x;
        w = globals.rail[i].pos.x;
        h = globals.rail[i].pos.y;
        x = globals.game_state.screen_w/2 - globals.game_state.screen_center.x + w * tile_size;
        y = globals.game_state.screen_h/2 - globals.game_state.screen_center.y + h * tile_size;
        al_draw_scaled_rotated_bitmap(globals.tiles.tile[TILE_RAIL_STRAIGHT], 32, 32, x+(tile_size/2), y+(tile_size/2), mult, mult, -ALLEGRO_PI/2, 0x0);

        w = globals.rail[i].pos_next.x;
        h = globals.rail[i].pos_next.y;
    while ((w != -1) && (h != -1)){
        i = h * tile_w + w;
        w_prev = globals.rail[i].pos_prev.x;
        h_prev = globals.rail[i].pos_prev.y;
        w_next = globals.rail[i].pos_next.x;
        h_next = globals.rail[i].pos_next.y;

        x = globals.game_state.screen_w/2 - globals.game_state.screen_center.x + w * tile_size;
        y = globals.game_state.screen_h/2 - globals.game_state.screen_center.y + h * tile_size;

        //check if not last rail piece
        //first was already set manually so it does not have to be checked
        if ((w_next != -1) && (h_next != -1)){
            dw0 = w - w_prev;
            dw1 = w_next - w;
            dh0 = h - h_prev;
            dh1 = h_next - h;
            //straight section in x direction
            if ((dw0 != 0) && (dw1 != 0)){
                al_draw_scaled_rotated_bitmap(globals.tiles.tile[TILE_RAIL_STRAIGHT], 32, 32, x+(tile_size/2), y+(tile_size/2), mult, mult, -ALLEGRO_PI/2, 0x0);
            }
            //straight section in y direction
            if ((dh0 != 0) && (dh1 != 0)){
                al_draw_scaled_rotated_bitmap(globals.tiles.tile[TILE_RAIL_STRAIGHT], 32, 32, x+(tile_size/2), y+(tile_size/2), mult, mult, 0, 0x0);
            }
            //corner section
            //N-E
            if ((dw0 == 0) && (dw1 == 1) && (dh0 == 1) && (dh1 == 0)){
                al_draw_scaled_rotated_bitmap(globals.tiles.tile[TILE_RAIL_CORNER], 32, 32, x+(tile_size/2), y+(tile_size/2), mult, mult, 0, 0x0);
            }
            //N-W
            if ((dw0 == 0) && (dw1 == -1) && (dh0 == 1) && (dh1 == 0)){
                al_draw_scaled_rotated_bitmap(globals.tiles.tile[TILE_RAIL_CORNER], 32, 32, x+(tile_size/2), y+(tile_size/2), mult, mult, -ALLEGRO_PI/2, 0x0);
            }
            //S-E
            if ((dw0 == 0) && (dw1 == 1) && (dh0 == -1) && (dh1 == 0)){
                al_draw_scaled_rotated_bitmap(globals.tiles.tile[TILE_RAIL_CORNER], 32, 32, x+(tile_size/2), y+(tile_size/2), mult, mult, ALLEGRO_PI/2, 0x0);
            }
            //W-S
            if ((dw0 == 1) && (dw1 == 0) && (dh0 == 0) && (dh1 == 1)){
                al_draw_scaled_rotated_bitmap(globals.tiles.tile[TILE_RAIL_CORNER], 32, 32, x+(tile_size/2), y+(tile_size/2), mult, mult, ALLEGRO_PI, 0x0);
            }
            //E-N
            if ((dw0 == -1) && (dw1 == 0) && (dh0 == 0) && (dh1 == -1)){
                al_draw_scaled_rotated_bitmap(globals.tiles.tile[TILE_RAIL_CORNER], 32, 32, x+(tile_size/2), y+(tile_size/2), mult, mult, 0, 0x0);
            }
            //E-S
            if ((dw0 == -1) && (dw1 == 0) && (dh0 == 0) && (dh1 == -1)){
                al_draw_scaled_rotated_bitmap(globals.tiles.tile[TILE_RAIL_CORNER], 32, 32, x+(tile_size/2), y+(tile_size/2), mult, mult, ALLEGRO_PI/2, 0x0);
            }
            //S-W
            if ((dw0 == 0) && (dw1 == -1) && (dh0 == -1) && (dh1 == 0)){
                al_draw_scaled_rotated_bitmap(globals.tiles.tile[TILE_RAIL_CORNER], 32, 32, x+(tile_size/2), y+(tile_size/2), mult, mult, ALLEGRO_PI, 0x0);
            }
            //W-N
            if ((dw0 == 1) && (dw1 == 0) && (dh0 == 0) && (dh1 == -1)){
                al_draw_scaled_rotated_bitmap(globals.tiles.tile[TILE_RAIL_CORNER], 32, 32, x+(tile_size/2), y+(tile_size/2), mult, mult, -ALLEGRO_PI/2, 0x0);
            }
        } else {
            //draw last tile
            al_draw_scaled_rotated_bitmap(globals.tiles.tile[TILE_RAIL_STRAIGHT], 32, 32, x+(tile_size/2), y+(tile_size/2), mult, mult, -ALLEGRO_PI/2, 0x0);
        }

        //set next position variables
        w = w_next;
        h = h_next;
    }

}

void draw_cursor_rect(void)
{
    float offset = 0.5f; //define pixels in the centre of a pixel area
    ALLEGRO_COLOR cursor_color0 = al_map_rgb(112,128,144); //slate gray
    ALLEGRO_COLOR cursor_color1 = al_map_rgb(176,196,222); //light steel blue

    float x,y;
    x = globals.mouse.grid_x;
    y = globals.mouse.grid_y;

    int tile_size = globals.tiles.tile_size;
    //float mult = globals.game_state.zoom_mult;

    al_draw_rectangle(x + offset + 1,y + offset + 1, x + tile_size-2 + offset,y + tile_size-2 + offset, cursor_color0, 3);
    al_draw_rectangle(x + offset + 1,y + offset + 1, x + tile_size-2 + offset,y + tile_size-2 + offset, cursor_color1, 1);
    if(globals.game_state.tower0_place == true){
        draw_tower_range(x, y, globals.tower_list->tower0->range);
        if (place_check() && price_check()){
            //can be build on this tile
            al_draw_tinted_scaled_bitmap(globals.ui_items[UI_BUILD_OK], al_map_rgba_f(1, 1, 1, 0.5), 0, 0, 64, 64, x , y, tile_size, tile_size, 0x0);
        } else {
            //can not be build on this tile
            al_draw_tinted_scaled_bitmap(globals.ui_items[UI_BUILD_BAD], al_map_rgba_f(1, 1, 1, 0.5), 0, 0, 64, 64, x , y, tile_size, tile_size, 0x0);
        }
    }
}

void draw_tower_range(float x, float y, float range){
    float mult = globals.game_state.zoom_mult;
    //draw the range circle, starting from the middle
    al_draw_circle(x + (32*mult), y + (32*mult), (range * mult) - 1, al_map_rgba(70,130,180, 128),3);
    al_draw_scaled_bitmap(globals.ui_items[UI_TWR_RANGE], 0, 0, 128, 128, x + (32 - range) * mult , y + (32 - range) * mult, 2 * range * mult, 2 * range * mult, 0x0);
}

void draw_top_bar(void)
{
    float offset = 0.5f; //define pixels in the centre of a pixel area

    ALLEGRO_COLOR base_color    = al_map_rgb(112,128,144); //slate gray
    ALLEGRO_COLOR border_color0 = al_map_rgb(119,136,153); //light slate gray
    ALLEGRO_COLOR border_color1 = al_map_rgb(176,196,222); //light steel blue

    float x0,y0,x1,y1;
    int screen_w,top_bar;
    screen_w = al_get_display_width(display);
    top_bar = globals.game_state.top_bar_h;
    x0 = 0;
    y0 = 0;
    x1 = screen_w;
    y1 = top_bar;
    //graphics
    al_draw_filled_rectangle(x0, y0, x1, y1, base_color);
    al_draw_rectangle(x0+1+offset, y0+1+offset, x1-1+offset, y1-1+offset, border_color0, 3);
    al_draw_rectangle(x0+1+offset, y0+1+offset, x1-1+offset, y1-1+offset, border_color1, 1);

    //text
    ALLEGRO_COLOR text_color0 = al_map_rgb(176,196,222); //light steel blue
    al_draw_textf(fonts[0] , text_color0, x0 + 10, y0 + 10, ALLEGRO_ALIGN_LEFT, "Credits: %6.1f",globals.game_state.credits);
    al_draw_textf(fonts[0] , text_color0, x0 + 300, y0 + 10, ALLEGRO_ALIGN_LEFT, "Energy: %4.f/%4.f",globals.game_state.energy_produced, globals.game_state.energy_required);
    al_draw_textf(fonts[0] , text_color0, x0 + 600, y0 + 10, ALLEGRO_ALIGN_LEFT, "Next: %3.1f",(float)globals.game_state.count_down/GAME_UPADTES_PER_SEC);
}

void draw_build_menu(void)
{
    if (globals.game_state.build_menu_on == true){
        float offset = 0.5f; //define pixels in the centre of a pixel area

        float x0,y0,x1,y1;
        int screen_w,screen_h,top_bar;
        screen_w = al_get_display_width(display);
        screen_h = al_get_display_height(display);
        top_bar = globals.game_state.top_bar_h;
        x0 = screen_w-globals.game_state.side_menu_w;
        y0 = top_bar;
        x1 = screen_w;
        y1 = screen_h;
        ALLEGRO_COLOR base_color    = al_map_rgb(112,128,144); //slate gray
        ALLEGRO_COLOR border_color0 = al_map_rgb(119,136,153); //light slate gray
        ALLEGRO_COLOR border_color1 = al_map_rgb(176,196,222); //light steel blue

        al_draw_filled_rectangle(x0, y0, x1, y1, base_color);
        al_draw_rectangle(x0+1+offset, y0+1+offset, x1-1+offset, y1-1+offset, border_color0, 3);
        al_draw_rectangle(x0+1+offset, y0+1+offset, x1-1+offset, y1-1+offset, border_color1, 1);

        ALLEGRO_COLOR plan_color            = al_map_rgb(135,206,235); //sky blue
        ALLEGRO_COLOR plan_selected_color   = al_map_rgb(139,0,139);

        if (globals.game_state.tower0_en == true){
            if(globals.game_state.tower0_place == true){
                al_draw_filled_rectangle(x0+25, y0+25, x0+25+64, y0+25+64, plan_selected_color);
            } else {
                al_draw_filled_rectangle(x0+25, y0+25, x0+25+64, y0+25+64, plan_color);
            }
            //draw tower base
            al_draw_bitmap(globals.objects[OBJ_TOWER], x0+25 , y0+25 , 0x0);
            //draw tower cannon
            al_draw_bitmap(globals.objects[OBJ_TOWER_GUN], x0+25, y0+25, 0x0);
        }
        if (globals.game_state.house0_en == true){
            if(globals.game_state.house0_place == true){
                al_draw_filled_rectangle(x0+25+64+22, y0+25, x0+25+64+22+64, y0+25+64, plan_selected_color);
            } else {
                al_draw_filled_rectangle(x0+25+64+22, y0+25, x0+25+64+22+64, y0+25+64, plan_color);
            }
        }
    }
}

void draw_enemy(void)
{
    float x,y;
    struct llist_t *cursor = globals.enemy;
    struct enemy_t *enemy;
    int tile_size = globals.tiles.tile_size;
    float mult = globals.game_state.zoom_mult;

    while(cursor != NULL){
        //convert virtual position to resized position

        enemy = cursor->ptr;

        x = globals.game_state.screen_w/2 - globals.game_state.screen_center.x + (enemy->position.x * mult);
        y = globals.game_state.screen_h/2 - globals.game_state.screen_center.y + (enemy->position.y * mult);
        //draw enemy
        al_draw_scaled_rotated_bitmap(globals.objects[OBJ_ENEMY], 32, 32, x+(tile_size/2), y+(tile_size/2), mult, mult, (rand()%360)*(2*ALLEGRO_PI)/360, 0x0);
        //al_draw_scaled_bitmap(globals.objects[OBJ_ENEMY], 0, 0, 64, 64, x , y , tile_size, tile_size, 0x0);
        //draw enemy health bar
        draw_health_bar(x, y, tile_size, enemy->max_health, enemy->health);
        cursor = cursor->next;
    }
}

void draw_health_bar(float x, float y, int len, float max, float value)
{
    //background base
    ALLEGRO_COLOR base_color    = al_map_rgb(127, 0, 0);
    al_draw_filled_rectangle(x, y, x+len, y+3, base_color);
    //line
    float ratio;
    if (value > 0) {
        ratio = value/max*len;
    } else {
        ratio = 0;
    }
    ALLEGRO_COLOR health_color    = al_map_rgb(255, 0, 0);
    al_draw_filled_rectangle(x, y, x+(int)ratio, y+3, health_color);
    //border
    ALLEGRO_COLOR border_color    = al_map_rgb(255, 255, 255);
    al_draw_rectangle(x, y, x+len, y+3, border_color, 1);
}

void draw_towers(void)
{
    float t_x,t_y,e_x,e_y;
    struct llist_t *cursor = globals.towers;
    struct tower_t *tower;
    int tile_size = globals.tiles.tile_size;
    float mult = globals.game_state.zoom_mult;

    while(cursor != NULL){
        tower = cursor->ptr;
        //convert virtual position to resized position

        t_x = globals.game_state.screen_w/2 - globals.game_state.screen_center.x + (tower->position.x * mult);
        t_y = globals.game_state.screen_h/2 - globals.game_state.screen_center.y + (tower->position.y * mult);
        //draw tower base
        al_draw_scaled_bitmap(globals.objects[OBJ_TOWER], 0, 0, 64, 64, t_x , t_y , tile_size, tile_size, 0x0);
        //draw beam
        if (tower->fire_active == true){
            e_x = globals.game_state.screen_w/2 - globals.game_state.screen_center.x + (tower->target->position.x * mult);
            e_y = globals.game_state.screen_h/2 - globals.game_state.screen_center.y + (tower->target->position.y * mult);
            al_draw_line(t_x+32*mult, t_y+32*mult, e_x+32*mult, e_y+32*mult, al_map_rgb(255, 0, 0), 3);
            al_draw_line(t_x+32*mult, t_y+32*mult, e_x+32*mult, e_y+32*mult, al_map_rgb(255, 255, 255), 1);
            al_draw_filled_circle(e_x+32*mult, e_y+32*mult, rand()%12, al_map_rgba(255, 0, 0, rand()%255));
            al_draw_filled_circle(e_x+32*mult, e_y+32*mult, rand()%8, al_map_rgba(255,255,255, rand()%255));
        }
        //draw tower cannon
        al_draw_scaled_rotated_bitmap(globals.objects[OBJ_TOWER_GUN], 32, 32, t_x+32*mult, t_y+32*mult, mult, mult, tower->angle, 0x0);

        cursor = cursor->next;
    }
}

void draw_floating_text(void)
{
    struct llist_t *cursor = globals.float_text;
    struct float_text_t *float_text;
    float x,y;
    float mult = globals.game_state.zoom_mult;


    while(cursor != NULL){
        float_text = cursor->ptr;
        //check if change of font height will be required!!!

        x = globals.game_state.screen_w/2 - globals.game_state.screen_center.x + (float_text->x * mult);
        y = globals.game_state.screen_h/2 - globals.game_state.screen_center.y + (float_text->y * mult);

        al_draw_text(fonts[0] , float_text->colour, x, y, ALLEGRO_ALIGN_LEFT, float_text->text);
        cursor = cursor->next;
    }
}
