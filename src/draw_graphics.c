
#include "draw_graphics.h"

void create_tiles(void)
{

    //TILE_BLANK 0
    globals.tiles.tile[TILE_BLANK] = al_create_bitmap(64, 64);
    al_set_target_bitmap(globals.tiles.tile[TILE_BLANK]);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    //TILE_LAND  1
    globals.tiles.tile[TILE_LAND] = al_create_bitmap(64, 64);
    al_set_target_bitmap(globals.tiles.tile[TILE_LAND]);
    al_clear_to_color(al_map_rgba(205, 133, 63, 255));
    //TILE_HILL  2
    globals.tiles.tile[TILE_HILL] = al_create_bitmap(64, 64);
    al_set_target_bitmap(globals.tiles.tile[TILE_HILL]);
    al_clear_to_color(al_map_rgba(205, 133, 63, 255));
    al_draw_filled_triangle(56, 56, 40, 16, 24, 56, al_map_rgb(139,69,19));
    al_draw_filled_triangle( 8, 56, 40, 56, 24, 24, al_map_rgb(210,105,30));
    //TILE_WATER 3
    globals.tiles.tile[TILE_WATER] = al_create_bitmap(64, 64);
    al_set_target_bitmap(globals.tiles.tile[TILE_WATER]);
    al_clear_to_color(al_map_rgba(135, 206, 250, 255));
    //TILE_GRASS 4
    globals.tiles.tile[TILE_GRASS] = al_create_bitmap(64, 64);
    al_set_target_bitmap(globals.tiles.tile[TILE_GRASS]);
    al_clear_to_color(al_map_rgba(50, 205, 50, 255));
    //TILE_ENEMY
    globals.tiles.tile[TILE_ENEMY] = al_create_bitmap(64, 64);
    al_set_target_bitmap(globals.tiles.tile[TILE_ENEMY]);
    al_clear_to_color(al_map_rgba(127, 0, 127, 255));

    //reselect the display buffer
    al_set_target_backbuffer(display);
}

void update_graphics(void)
{
    draw_background();
    draw_map();
    draw_cursor_rect();
    draw_enemy();
    draw_build_menu();
}

void draw_background(void)
{
    //black background
    al_clear_to_color(al_map_rgb(0, 0, 0)); //black background
}

void draw_map(void)
{

    int w,h;
    int tile_type;
    float x,y;

    int tile_size;

    float offset = 0.5; //define pixels in the center of a pixel area
    ALLEGRO_COLOR grid_color = al_map_rgb(0, 0, 0);  //black

    tile_size = globals.tiles.tile_size;

    for (h = 0; h < globals.tiles.tile_h; h++){
        for (w = 0; w < globals.tiles.tile_w; w++){
            //add check to only raw the visible tiles instead of the whole map!!
            x = globals.game_state.screen_w/2 - globals.game_state.screen_center.x + w * tile_size;
            y = globals.game_state.screen_h/2 - globals.game_state.screen_center.y + h * tile_size;
            tile_type = globals.tiles.p[h*globals.tiles.tile_w+w];
            if (tile_type == TILE_BLANK){
                al_draw_scaled_bitmap(globals.tiles.tile[TILE_BLANK], 0, 0, 64, 64, x , y , tile_size, tile_size,  0x0);
            }
            if (tile_type == TILE_LAND){
                al_draw_scaled_bitmap(globals.tiles.tile[TILE_LAND], 0, 0, 64, 64, x , y , tile_size, tile_size, 0x0);
            }
            if (tile_type == TILE_HILL){
                al_draw_scaled_bitmap(globals.tiles.tile[TILE_HILL], 0, 0, 64, 64, x , y , tile_size, tile_size, 0x0);
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

void draw_cursor_rect(void)
{
    float offset = 0.5; //define pixels in the centre of a pixel area
    ALLEGRO_COLOR cursor_color = al_map_rgb(255, 0, 0);  //red
    float x,y;
    float mouse_x,mouse_y;

    int tile_size;
    tile_size = globals.tiles.tile_size;

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

    x = globals.game_state.screen_center.x - globals.game_state.screen_w/2 + mouse_x;
    if (x < 0){
        x = 0;
    } else if (x >= globals.tiles.tile_w * tile_size){
        x = (globals.tiles.tile_w-1) * tile_size;
    } else {
        x = (int)(x/tile_size)*tile_size;
    }
    x = x - (globals.game_state.screen_center.x - globals.game_state.screen_w/2);
    y = globals.game_state.screen_center.y - globals.game_state.screen_h/2 + mouse_y;
    if (y < 0){
        y = 0;
    } else if (y >= globals.tiles.tile_h * tile_size){
        y = (globals.tiles.tile_h-1) * tile_size;
    } else {
        y = (int)(y/tile_size)*tile_size;
    }
    y = y - (globals.game_state.screen_center.y - globals.game_state.screen_h/2);

    al_draw_rectangle(x + offset,y + offset, x + tile_size-1 + offset,y + tile_size-1 + offset, cursor_color, 2);
}

void draw_build_menu(void)
{
    if (globals.game_state.build_menu_on == true){
        float offset = 0.5; //define pixels in the centre of a pixel area

        float x0,y0,x1,y1;
        int screen_w,screen_h;
        screen_w = al_get_display_width(display);
        screen_h = al_get_display_height(display);
        x0 = screen_w-globals.game_state.side_menu_w + offset;
        y0 = offset;
        x1 = screen_w + offset;
        y1 = screen_h + offset;
        ALLEGRO_COLOR base_color    = al_map_rgb(112,128,144); //slate gray
        ALLEGRO_COLOR border_color0 = al_map_rgb(119,136,153); //light slate gray
        ALLEGRO_COLOR border_color1 = al_map_rgb(176,196,222); //light steel blue

        al_draw_filled_rectangle(x0, y0, x1, y1, base_color);
        al_draw_rectangle(x0+1, y0+1, x1-1, y1-1, border_color0, 3);
        al_draw_rectangle(x0+2, y0+2, x1-2, y1-2, border_color1, 1);

        if (globals.game_state.tower0_en == true){
            ALLEGRO_COLOR tower0_color    = al_map_rgb(192,192,192); //silver
            al_draw_filled_rectangle(x0+19, y0+19, x0+19+63, y0+19+63, tower0_color);
        }
        if (globals.game_state.house0_en == true){
            ALLEGRO_COLOR house0_color    = al_map_rgb(154,205,50); //yellow green
            al_draw_filled_rectangle(x0+100, y0+19, x0+100+63, y0+19+63, house0_color);
        }
    }
}

void draw_enemy(void)
{
    int tile_size;
    struct enemy_t *cursor = globals.enemy;

    tile_size = globals.tiles.tile_size;

    if (cursor != NULL){
        while(cursor->next != NULL){
            al_draw_scaled_bitmap(globals.tiles.tile[TILE_ENEMY], 0, 0, 64, 64, cursor->position.x , cursor->position.y , tile_size, tile_size, 0x0);
            cursor = cursor->next;
        }
    }
}
