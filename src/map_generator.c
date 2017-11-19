
#include "map_generator.h"

void generate_map(void)
{
    int h,w,sel;
    int tile_h, tile_w;
    bool tile_NE,tile_N,tile_NW,tile_E,tile_W,tile_SE,tile_S,tile_SW;

    tile_w = globals.tiles.tile_w;
    tile_h = globals.tiles.tile_h;

    int *hill = (int*)malloc(sizeof(int) * tile_w * tile_h);

    //fill the tile map memory with land tiles
    for (h = 0; h < tile_h; h++){
        for (w = 0; w < tile_w; w++){
            globals.tiles.p[h*tile_w + w] = TILE_LAND;
            //randomly set tiles as hills
            sel = ((rand()%3) > 0) ? 0 : -1;
            hill[h*tile_w + w] = sel;
        }
    }

    //use appropriate hill sprite for set hill configuration
    for (h = 0; h < tile_h; h++){
        for (w = 0; w < tile_w; w++){
            //if tile is a hill
            if (hill[h*tile_w + w] == -1){
                //check all 8 tiles around the selected tile
                //tiles outside the map are a hill tile by default
                if ((w > 0) && (h > 0)){
                    tile_NW = (hill[(h-1)*tile_w + (w-1)] == -1);
                } else {
                    tile_NW = true;
                }
                if (h > 0){
                    tile_N = (hill[(h-1)*tile_w + w] == -1);
                } else {
                    tile_N = true;
                }
                if ((w < tile_w-1) && (h > 0)){
                    tile_NE = (hill[(h-1)*tile_w + (w+1)] == -1);
                } else {
                    tile_NE = true;
                }
                if (w > 0){
                    tile_W = (hill[h*tile_w + w] == -1);
                } else {
                    tile_W = true;
                }
                if (w < tile_w-1){
                    tile_E = (hill[h*tile_w + (w+1)] == -1);
                } else {
                    tile_E = true;
                }
                if ((w > 0) && (h < tile_h-1)){
                    tile_SW = (hill[(h+1)*tile_w + (w-1)] == -1);
                } else {
                    tile_SW = true;
                }
                if (h < tile_h-1){
                    tile_S = (hill[(h+1)*tile_w + w] == -1);
                } else {
                    tile_S = true;
                }
                if ((w < tile_w-1) && (h < tile_h-1)){
                    tile_SE = (hill[(h+1)*tile_w + (w+1)] == -1);
                } else {
                    tile_SE = true;
                }
                //select correct hill sprite
                if ( tile_W &&  tile_N &&  tile_E &&  tile_S){
                    globals.tiles.hill[h*tile_w + w] = 0x0;
                }
                if (!tile_W && !tile_N &&  tile_E &&  tile_S){
                    globals.tiles.hill[h*tile_w + w] = TILE_ID_HILL_0;
                }
                if (tile_W && tile_E && !tile_N){
                    globals.tiles.hill[h*tile_w + w] = TILE_ID_HILL_1;
                }
                if (!tile_S && !tile_N){
                    globals.tiles.hill[h*tile_w + w] = TILE_ID_HILL_2;
                }
                if (!tile_N && !tile_W && !tile_E && !tile_S){
                    globals.tiles.hill[h*tile_w + w] = TILE_ID_HILL_7;
                }
            } else {
                globals.tiles.hill[h*tile_w + w] = 0x0;

            }

        }
    }
}
