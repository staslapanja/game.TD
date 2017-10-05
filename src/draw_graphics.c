
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
    //TILE_OK     5
    globals.tiles.tile[TILE_OK] = al_create_bitmap(64, 64);
    al_set_target_bitmap(globals.tiles.tile[TILE_OK]);
    al_draw_line( 0,47, 16, 63, al_map_rgb(0, 255, 0), 2);
    al_draw_line( 0,31, 32, 63, al_map_rgb(0, 255, 0), 2);
    al_draw_line( 0,15, 48, 63, al_map_rgb(0, 255, 0), 2);
    al_draw_line( 0, 0, 63, 63, al_map_rgb(0, 255, 0), 2);
    al_draw_line(16, 0, 63, 47, al_map_rgb(0, 255, 0), 2);
    al_draw_line(32, 0, 63, 31, al_map_rgb(0, 255, 0), 2);
    al_draw_line(48, 0, 63, 15, al_map_rgb(0, 255, 0), 2);
    //TILE_BAD    6
    globals.tiles.tile[TILE_BAD] = al_create_bitmap(64, 64);
    al_set_target_bitmap(globals.tiles.tile[TILE_BAD]);
    al_draw_line( 0,15, 15, 0, al_map_rgb(255, 0, 0), 2);
    al_draw_line( 0,31, 31, 0, al_map_rgb(255, 0, 0), 2);
    al_draw_line( 0,47, 47, 0, al_map_rgb(255, 0, 0), 2);
    al_draw_line( 0,63, 63, 0, al_map_rgb(255, 0, 0), 2);
    al_draw_line(15,63, 63,15, al_map_rgb(255, 0, 0), 2);
    al_draw_line(31,63, 63,31, al_map_rgb(255, 0, 0), 2);
    al_draw_line(47,63, 63,47, al_map_rgb(255, 0, 0), 2);
    //TILE_RAIL_STRAIGHT  7
    globals.tiles.tile[TILE_RAIL_STRAIGHT] = al_create_bitmap(64, 64);
    al_set_target_bitmap(globals.tiles.tile[TILE_RAIL_STRAIGHT]);
    al_draw_filled_rectangle(16+0.5, 0+0.5, 47+0.5, 64+0.5, al_map_rgb(105,105,105));//dim gray / dim grey
    al_draw_filled_rectangle(30+0.5, 0+0.5, 33+0.5, 64+0.5, al_map_rgb(75,0,130));//indigo
    //TILE_RAIL_CORNER    8
    globals.tiles.tile[TILE_RAIL_CORNER] = al_create_bitmap(64, 64);
    al_set_target_bitmap(globals.tiles.tile[TILE_RAIL_CORNER]);
    al_draw_filled_rectangle(16+0.5, 0+0.5, 47+0.5, 47+0.5, al_map_rgb(105,105,105));//dim gray / dim grey
    al_draw_filled_rectangle(48+0.5, 16+0.5,64+0.5, 47+0.5, al_map_rgb(105,105,105));//dim gray / dim grey
    al_draw_filled_rectangle(30+0.5, 0+0.5, 33+0.5, 33+0.5, al_map_rgb(75,0,130));//indigo
    al_draw_filled_rectangle(34+0.5,30+0.5, 64+0.5, 33+0.5, al_map_rgb(75,0,130));//indigo

    //reselect the display buffer
    al_set_target_backbuffer(display);


}

void create_game_objects(void)
{
    //OBJ_ENEMY
    globals.objects[OBJ_ENEMY] = al_create_bitmap(64, 64);
    al_set_target_bitmap(globals.objects[OBJ_ENEMY]);
    al_draw_filled_circle(32, 32, 16, al_map_rgba(127, 0, 127, 255));
    //OBJ_TOWER
    globals.objects[OBJ_TOWER] = al_create_bitmap(64, 64);
    al_set_target_bitmap(globals.objects[OBJ_TOWER]);
    al_draw_filled_rectangle(8, 8, 56, 56, al_map_rgba(119,136,153, 255));
    //OBJ_TOWER_GUN
    globals.objects[OBJ_TOWER_GUN] = al_create_bitmap(64, 64);
    al_set_target_bitmap(globals.objects[OBJ_TOWER_GUN]);
    al_draw_filled_circle(32, 32, 16, al_map_rgba(176,196,222, 255));
    al_draw_line(32, 32, 32, 0, al_map_rgb(0, 0, 0), 5);

    //reselect the display buffer
    al_set_target_backbuffer(display);
}

void init_graphics(void)
{
    create_tiles();
    create_game_objects();
}

void update_graphics(void)
{
    draw_background();
    draw_map();
    draw_rail();
    draw_enemy();
    draw_towers();
    draw_cursor_rect();
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
    bool place_tower, place_house;

    int tile_size;

    float offset = 0.5; //define pixels in the center of a pixel area
    ALLEGRO_COLOR grid_color = al_map_rgb(0, 0, 0);  //black

    tile_size = globals.tiles.tile_size;
    place_tower = (globals.game_state.tower0_place == true) || (globals.game_state.tower1_place == true);
    place_house = (globals.game_state.house0_place == true) || (globals.game_state.house1_place == true);

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
                if (place_tower || place_house){
                    al_draw_scaled_bitmap(globals.tiles.tile[TILE_OK], 0, 0, 64, 64, x , y , tile_size, tile_size,  0x0);
                }
            }
            if (tile_type == TILE_HILL){
                al_draw_scaled_bitmap(globals.tiles.tile[TILE_HILL], 0, 0, 64, 64, x , y , tile_size, tile_size, 0x0);
                if (place_tower){
                    al_draw_scaled_bitmap(globals.tiles.tile[TILE_OK], 0, 0, 64, 64, x , y , tile_size, tile_size,  0x0);
                }
                if (place_house){
                    al_draw_scaled_bitmap(globals.tiles.tile[TILE_BAD], 0, 0, 64, 64, x , y , tile_size, tile_size,  0x0);
                }
            }
            if (tile_type == TILE_WATER){
                al_draw_scaled_bitmap(globals.tiles.tile[TILE_WATER], 0, 0, 64, 64, x , y , tile_size, tile_size, 0x0);
                if (place_tower || place_house){
                    al_draw_scaled_bitmap(globals.tiles.tile[TILE_BAD], 0, 0, 64, 64, x , y , tile_size, tile_size,  0x0);
                }
            }
            if (tile_type == TILE_GRASS){
                al_draw_scaled_bitmap(globals.tiles.tile[TILE_GRASS], 0, 0, 64, 64, x , y , tile_size, tile_size, 0x0);
                if (place_tower || place_house){
                    al_draw_scaled_bitmap(globals.tiles.tile[TILE_OK], 0, 0, 64, 64, x , y , tile_size, tile_size,  0x0);
                }
            }
            //draw grid around the tile if enabled
            if (globals.game_state.grid_en == true){
                al_draw_rectangle(x + offset,y + offset, x + tile_size-1 + offset,y + tile_size-1 + offset, grid_color, 1);
            }
        }
    }

}

void draw_rail(void)
{
    int w,h,i;
    int w_prev,h_prev,w_next,h_next;
    int dw0, dw1, dh0, dh1;
    float x,y;
    int tile_size;
    float mult;
    float offset = 0.5; //define pixels in the center of a pixel area

    tile_size = globals.tiles.tile_size;
    mult = tile_size/64;

    i = 0;
        w = globals.rail[i].pos.x;
        h = globals.rail[i].pos.y;
        x = globals.game_state.screen_w/2 - globals.game_state.screen_center.x + w * tile_size;
        y = globals.game_state.screen_h/2 - globals.game_state.screen_center.y + h * tile_size;
        al_draw_scaled_rotated_bitmap(globals.tiles.tile[TILE_RAIL_STRAIGHT], 0, 0, x+offset, y+(63*mult)+offset, mult, mult, -ALLEGRO_PI/2, 0x0);

        w = globals.rail[i].pos_next.x;
        h = globals.rail[i].pos_next.y;
    while ((w != -1) && (h != -1)){
        i++;
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
                al_draw_scaled_rotated_bitmap(globals.tiles.tile[TILE_RAIL_STRAIGHT], 0, 0, x+offset, y+(63*mult)+offset, mult, mult, -ALLEGRO_PI/2, 0x0);
            }
            //straight section in y direction
            if ((dh0 != 0) && (dh1 != 0)){
                al_draw_scaled_rotated_bitmap(globals.tiles.tile[TILE_RAIL_STRAIGHT], 0, 0, x+offset, y+offset, mult, mult, 0, 0x0);
            }
            //corner section
            //N-E
            if ((dw0 == 0) && (dw1 == 1) && (dh0 == 1) && (dh1 == 0)){
                al_draw_scaled_rotated_bitmap(globals.tiles.tile[TILE_RAIL_CORNER], 0, 0, x+offset, y+offset, mult, mult, 0, 0x0);
            }
            //N-W
            if ((dw0 == 0) && (dw1 == -1) && (dh0 == 1) && (dh1 == 0)){
                al_draw_scaled_rotated_bitmap(globals.tiles.tile[TILE_RAIL_CORNER], 0, 63, x+(63*mult)+offset, y+(63*mult)+offset, mult, mult, -ALLEGRO_PI/2, 0x0);
            }
            //S-E
            if ((dw0 == 0) && (dw1 == 1) && (dh0 == -1) && (dh1 == 0)){
                al_draw_scaled_rotated_bitmap(globals.tiles.tile[TILE_RAIL_CORNER], 0, 0, x+(63*mult)+offset, y+offset, mult, mult, ALLEGRO_PI/2, 0x0);
            }
            //W-S
            if ((dw0 == 1) && (dw1 == 0) && (dh0 == 0) && (dh1 == 1)){
                al_draw_scaled_rotated_bitmap(globals.tiles.tile[TILE_RAIL_CORNER], 63, 63, x+offset, y+offset, mult, mult, ALLEGRO_PI, 0x0);
            }
            //E-N
            if ((dw0 == -1) && (dw1 == 0) && (dh0 == 0) && (dh1 == -1)){
                al_draw_scaled_rotated_bitmap(globals.tiles.tile[TILE_RAIL_CORNER], 0, 0, x+offset, y+offset, mult, mult, 0, 0x0);
            }
            //E-S
            if ((dw0 == -1) && (dw1 == 0) && (dh0 == 0) && (dh1 == -1)){
                al_draw_scaled_rotated_bitmap(globals.tiles.tile[TILE_RAIL_CORNER], 0, 0, x+(63*mult)+offset, y+offset, mult, mult, ALLEGRO_PI/2, 0x0);
            }
            //S-W
            if ((dw0 == 0) && (dw1 == -1) && (dh0 == -1) && (dh1 == 0)){
                al_draw_scaled_rotated_bitmap(globals.tiles.tile[TILE_RAIL_CORNER], 63, 63, x+offset, y+offset, mult, mult, ALLEGRO_PI, 0x0);
            }
            //W-N
            if ((dw0 == 1) && (dw1 == 0) && (dh0 == 0) && (dh1 == -1)){
                al_draw_scaled_rotated_bitmap(globals.tiles.tile[TILE_RAIL_CORNER], 0, 63, x+(63*mult)+offset, y+(63*mult)+offset, mult, mult, -ALLEGRO_PI/2, 0x0);
            }
        } else {
            //draw last tile
            al_draw_scaled_rotated_bitmap(globals.tiles.tile[TILE_RAIL_STRAIGHT], 0, 0, x+offset, y+(63*mult)+offset, mult, mult, -ALLEGRO_PI/2, 0x0);
        }

        //set next position variables
        w = w_next;
        h = h_next;
    }

}

void draw_cursor_rect(void)
{
    float offset = 0.5; //define pixels in the centre of a pixel area
    ALLEGRO_COLOR cursor_color0 = al_map_rgb(112,128,144); //slate gray
    ALLEGRO_COLOR cursor_color1 = al_map_rgb(176,196,222); //light steel blue

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

    al_draw_rectangle(x + offset + 1,y + offset + 1, x + tile_size-2 + offset,y + tile_size-2 + offset, cursor_color0, 3);
    al_draw_rectangle(x + offset + 1,y + offset + 1, x + tile_size-2 + offset,y + tile_size-2 + offset, cursor_color1, 1);
    if(globals.game_state.tower0_place == true){
        //draw tower base
        al_draw_tinted_scaled_bitmap(globals.objects[OBJ_TOWER], al_map_rgba_f(1, 1, 1, 0.5), 0, 0, 64, 64, x , y, tile_size, tile_size, 0x0);
        //draw tower cannon
        al_draw_tinted_scaled_bitmap(globals.objects[OBJ_TOWER_GUN],al_map_rgba_f(1, 1, 1, 0.5), 0, 0, 64, 64, x , y, tile_size, tile_size, 0x0);
    }
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

        ALLEGRO_COLOR plan_color    = al_map_rgb(135,206,235); //sky blue
        ALLEGRO_COLOR plan_selected_color    = al_map_rgb(139,0,139); //sky blue

        if (globals.game_state.tower0_en == true){
            if(globals.game_state.tower0_place == true){
                al_draw_filled_rectangle(x0+19, y0+19, x0+19+63, y0+19+63, plan_selected_color);
            } else {
                al_draw_filled_rectangle(x0+19, y0+19, x0+19+63, y0+19+63, plan_color);
            }
            //draw tower base
            al_draw_bitmap(globals.objects[OBJ_TOWER], x0+19 , y0+19 , 0x0);
            //draw tower cannon
            al_draw_bitmap(globals.objects[OBJ_TOWER_GUN], x0+19, y0+19, 0x0);
        }
        if (globals.game_state.house0_en == true){
            if(globals.game_state.house0_place == true){
                al_draw_filled_rectangle(x0+19, y0+19, x0+19+63, y0+19+63, plan_selected_color);
            } else {
                al_draw_filled_rectangle(x0+19, y0+19, x0+19+63, y0+19+63, plan_color);
            }
        }
    }
}

void draw_enemy(void)
{
    float x,y;
    int tile_size;
    struct enemy_t *cursor = globals.enemy;

    tile_size = globals.tiles.tile_size;

    while(cursor != NULL){
        //conver virtual position to resized position
        float mult;
        switch(globals.game_state.zoom){
            case 0:
                mult = 0.5;
                break;
            case 1:
                mult = 1;
                break;
            case 2:
                mult = 2;
                break;
            default:
                mult = 1;
                break;
        }
        x = globals.game_state.screen_w/2 - globals.game_state.screen_center.x + (cursor->position.x * mult);
        y = globals.game_state.screen_h/2 - globals.game_state.screen_center.y + (cursor->position.y * mult);
        //draw enemy
        al_draw_scaled_bitmap(globals.objects[OBJ_ENEMY], 0, 0, 64, 64, x , y , tile_size, tile_size, 0x0);
        //draw enemy healthbar
        draw_health_bar(x, y, tile_size, cursor->max_health, cursor->health);
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
    int tile_size;
    struct tower_t *cursor = globals.towers;
    tile_size = globals.tiles.tile_size;

    while(cursor != NULL){
        //convert virtual position to resized position
        float mult;
        switch(globals.game_state.zoom){
            case 0:
                mult = 0.5;
                break;
            case 1:
                mult = 1;
                break;
            case 2:
                mult = 2;
                break;
            default:
                mult = 1;
                break;
        }
        t_x = globals.game_state.screen_w/2 - globals.game_state.screen_center.x + (cursor->position.x * mult);
        t_y = globals.game_state.screen_h/2 - globals.game_state.screen_center.y + (cursor->position.y * mult);
        //draw tower base
        al_draw_scaled_bitmap(globals.objects[OBJ_TOWER], 0, 0, 64, 64, t_x , t_y , tile_size, tile_size, 0x0);
        //draw beam
        if (cursor->fire_active == true){
            e_x = globals.game_state.screen_w/2 - globals.game_state.screen_center.x + (cursor->target->position.x * mult);
            e_y = globals.game_state.screen_h/2 - globals.game_state.screen_center.y + (cursor->target->position.y * mult);
            al_draw_line(t_x+32*mult, t_y+32*mult, e_x+32*mult, e_y+32*mult, al_map_rgb(255, 0, 0), 3);
            al_draw_line(t_x+32*mult, t_y+32*mult, e_x+32*mult, e_y+32*mult, al_map_rgb(255, 255, 255), 1);
            al_draw_filled_circle(e_x+32*mult, e_y+32*mult, rand()%12, al_map_rgba(255, 0, 0, rand()%255));
            al_draw_filled_circle(e_x+32*mult, e_y+32*mult, rand()%8, al_map_rgba(255,255,255, rand()%255));
        }
        //draw tower cannon
        al_draw_scaled_rotated_bitmap(globals.objects[OBJ_TOWER_GUN], 32, 32, t_x+32*mult, t_y+32*mult, mult, mult, cursor->angle, 0x0);

        cursor = cursor->next;
    }
}
