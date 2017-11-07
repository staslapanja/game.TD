
#include "map_generator.h"

void generate_map(void)
{
    int h,w,sel;
    int tile_h, tile_w;
    bool tile_NE,tile_N,tile_NW,tile_E,tile_W,tile_SE,tile_S,tile_SW;

    tile_w = globals.tiles.tile_w;
    tile_h = globals.tiles.tile_h;

    //fill the tile map memory with land tiles
    for (h = 0; h < tile_h; h++){
        for (w = 0; w < tile_w; w++){
            globals.tiles.p[h*tile_w + w] = TILE_LAND;
            //randomly set tiles as hills
            sel = ((rand()%3) > 0) ? 0 : -1;
            globals.tiles.hill[h*tile_w + w] = sel;
        }
    }

    //use appropriate hill sprite for set hill configuration
    for (h = 0; h < tile_h; h++){
        for (w = 0; w < tile_w; w++){
            //if tile is a hill
            if (globals.tiles.hill[h*tile_w + w] == -1){
                //check all 8 tiles around the selected tile
                if ((w > 0) && (h > 0)){
                    tile_NW = (globals.tiles.hill[(h-1)*tile_w + (w-1)] == -1);
                } else {
                    tile_NW = true;
                }
                if (h > 0){
                    tile_N = (globals.tiles.hill[(h-1)*tile_w + w] == -1);
                } else {
                    tile_N = true;
                }
                if (w < tile_w-1){
                    tile_NE = (globals.tiles.hill[(h-1)*tile_w + (w+1)] == -1);
                } else {
                    tile_NE = true;
                }
                //tiles outside the map are a hill tile
            }

        }
    }
}
