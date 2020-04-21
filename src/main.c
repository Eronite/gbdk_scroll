#include <C:\Users\FDO\Desktop\test_scroll\src\gbdk\include\gb\gb.h>
#include <C:\Users\FDO\Desktop\test_scroll\src\gbdk\include\gb\console.h>
#include "BackgroundTiles.c"
#include "BackgroundMap3.c"
#include "Sprites.c"

const char blankmap[1] = {0x00};
UINT16 playerlocation[2];
UBYTE gamerunning;
UINT8 flip = 0;
UBYTE direction = 0;

#define MapSizeX 64
#define MapSizeY 64
UWORD scrollX = 0;   // UBYTE
UWORD scrollY = 0;   // UBYTE
BYTE tileCounterX = 0 ;
BYTE tileCounterY = 0 ; 
UBYTE i = 0;
UBYTE tempX = 0;
UBYTE tempY = 0;
UWORD counterX = 0;
UWORD counterY = 0;

#define PLAYER_SPRITE_L_ID 0
#define PLAYER_SPRITE_R_ID 1


void performantdelay(UINT8 numloops){
    UINT8 i;
    for(i = 0; i < numloops; i++){
        wait_vbl_done();
    }     
}

void anim_walking_left()
{
    set_sprite_prop(0, get_sprite_prop(0) & ~S_FLIPY);
    set_sprite_prop(1, get_sprite_prop(1) & ~S_FLIPY);

    set_sprite_prop(0, get_sprite_prop(0) & ~S_FLIPX);
    set_sprite_prop(1, get_sprite_prop(1) & ~S_FLIPX);

    if (flip == 1)
    {
        set_sprite_tile(PLAYER_SPRITE_L_ID,16);
        set_sprite_tile(PLAYER_SPRITE_R_ID,18);
        flip = 0;
    }
    else
    {
        set_sprite_tile(PLAYER_SPRITE_L_ID,20);
        set_sprite_tile(PLAYER_SPRITE_R_ID,22);
        flip = 1;
    }

    direction = 1;
}

void anim_walking_right()
{
    set_sprite_prop(0, get_sprite_prop(0) & ~S_FLIPY);
    set_sprite_prop(1, get_sprite_prop(1) & ~S_FLIPY);

    set_sprite_prop(0, get_sprite_prop(0) & ~S_FLIPX);
    set_sprite_prop(1, get_sprite_prop(1) & ~S_FLIPX);

    if (flip == 1)
    {
        set_sprite_tile(PLAYER_SPRITE_L_ID,24);
        set_sprite_tile(PLAYER_SPRITE_R_ID,26);
        flip = 0;
    }
    else
    {
        set_sprite_tile(PLAYER_SPRITE_L_ID,28);
        set_sprite_tile(PLAYER_SPRITE_R_ID,30);
        flip = 1;
    }

    direction = 3;
}

void anim_walking_up()
{
    set_sprite_prop(0, get_sprite_prop(0) & ~S_FLIPY);
    set_sprite_prop(1, get_sprite_prop(1) & ~S_FLIPY);

    set_sprite_prop(0, get_sprite_prop(0) & ~S_FLIPX);
    set_sprite_prop(1, get_sprite_prop(1) & ~S_FLIPX);

    if (flip == 1)
    {
        set_sprite_tile(PLAYER_SPRITE_L_ID,0);
        set_sprite_tile(PLAYER_SPRITE_R_ID,2);
        flip = 0;
    }
    else
    {
        set_sprite_tile(PLAYER_SPRITE_L_ID,4);
        set_sprite_tile(PLAYER_SPRITE_R_ID,6);
        flip = 1;
    }

    direction = 2;
}

void anim_walking_down()
{
    set_sprite_prop(0, get_sprite_prop(0) & ~S_FLIPY);
    set_sprite_prop(1, get_sprite_prop(1) & ~S_FLIPY);

    set_sprite_prop(0, get_sprite_prop(0) & ~S_FLIPX);
    set_sprite_prop(1, get_sprite_prop(1) & ~S_FLIPX);

    if (flip == 1)
    {
        set_sprite_tile(PLAYER_SPRITE_L_ID,8);
        set_sprite_tile(PLAYER_SPRITE_R_ID,10);
        flip = 0;
    }
    else
    {
        set_sprite_tile(PLAYER_SPRITE_L_ID,12);
        set_sprite_tile(PLAYER_SPRITE_R_ID,14);
        flip = 1;
    }

    direction = 0;
}


void main(){

    disable_interrupts;

    set_bkg_data(0, 85, BackgroundTiles);

    counterX = 0;
    for (i = 0; i != 19; i++ )
    {
        set_bkg_tiles(0, i, 21, 1, (BackgroundMap3+counterX));
        counterX = counterX + MapSizeX;
    }

    set_sprite_data(0, 108, Sprites);

    SPRITES_8x16;
    SHOW_SPRITES;
    SHOW_BKG;
    DISPLAY_ON;

    enable_interrupts();

    set_sprite_prop(0, get_sprite_prop(0) & ~S_FLIPX);
    set_sprite_prop(1, get_sprite_prop(1) & ~S_FLIPX);
    set_sprite_tile(PLAYER_SPRITE_L_ID,8);
    set_sprite_tile(PLAYER_SPRITE_R_ID,10);

    playerlocation[0] = 80;
    playerlocation[1] = 80;

    move_sprite(PLAYER_SPRITE_L_ID, playerlocation[0], playerlocation[1]);
    move_sprite(PLAYER_SPRITE_R_ID, playerlocation[0] + 8, playerlocation[1]);

    gamerunning = 1;

    while(gamerunning)
    {
        performantdelay(8);

        if(joypad() & J_A)
        {

        }

        if((joypad() & J_LEFT) && (scrollX !=0))
        {
            scroll_bkg(-8, 0);
            tileCounterX = tileCounterX-8;

            anim_walking_left();
        }

        if((joypad() & J_RIGHT) && (scrollX < MapSizeX-20 ))
        {
            scroll_bkg(8, 0);
            tileCounterX = tileCounterX+8;

            anim_walking_right();
        }

        if (tileCounterX == 8)
        {
            scrollX++;
            tileCounterX = 0;

            counterX = scrollX + 19;
            tempX = counterX % 32;
            counterY = scrollY * MapSizeY;

            for (i = 0; i != 19; i++)
            {
                set_bkg_tiles(tempX, i + (scrollY % 32), 1, 1, (BackgroundMap3+counterX+counterY));
                counterX = counterX + MapSizeX;
            }
        }

        if (tileCounterX == -8)
        {
            scrollX--;
            tileCounterX = 0;

            counterX = scrollX-2;
            tempX = counterX % 32;
            counterY = scrollY * MapSizeY;

            for (i = 0; i != 20; i++)
            {
                set_bkg_tiles(tempX, i + (scrollY % 32), 1, 1, (BackgroundMap3+counterX+counterY));
                counterX = counterX + MapSizeX;
            }
        }


        if((joypad() & J_UP) && (scrollY !=0))
        {
            scroll_bkg(0, -8);
            tileCounterY = tileCounterY-8;

            anim_walking_up();
        }

        if((joypad() & J_DOWN) && (scrollY < MapSizeY-18 ))
        {
            scroll_bkg(0, 8);
            tileCounterY = tileCounterY+8;

            anim_walking_down();
        }

        if (tileCounterY == 8)
        {
            scrollY++;
            tileCounterY = 0;

            counterY = (scrollY + 18) * MapSizeY;
            tempY = (scrollY + 18) % 32;
            tempX = scrollX % 32;
            counterX = scrollX;

            set_bkg_tiles(tempX, tempY, 22, 1, (BackgroundMap3+counterY+counterX));
        }

        if (tileCounterY == -8)
        {
            scrollY--;
            tileCounterY = 0;

            counterY = (scrollY - 1) * MapSizeX;
            tempY = (scrollY - 1) % 32;
            counterX = scrollX;
            tempX = scrollX % 32;

            set_bkg_tiles(tempX, tempY, 22, 1, (BackgroundMap3+counterY+counterX));
            counterY = counterY + MapSizeY;
        }   
    }
}