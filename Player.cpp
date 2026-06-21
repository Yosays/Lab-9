#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "player.h"

player::player(int HEIGHT)
{
    // load all kirby frames into array
    images[0] = al_load_bitmap("kirby0.png");
    images[1] = al_load_bitmap("kirby1.png");
    images[2] = al_load_bitmap("kirby2.png");
    images[3] = al_load_bitmap("kirby3.png");
    images[4] = al_load_bitmap("kirby4.png");

    x = 20;
    y = HEIGHT / 2;
    lives = 5;
    speed = 7;
    boundx = al_get_bitmap_width(images[0]);
    boundy = al_get_bitmap_height(images[0]);
    score = 0;
    imageIndex = 0;
    hitTimer = 0;
}

player::~player()
{
    for (int i = 0; i < 5; i++)
        al_destroy_bitmap(images[i]);
}

void player::removeLife()
{
    lives--;
    // cycle to next damage frame and hold it for 60 ticks
    imageIndex = (imageIndex % 4) + 1;   // stays in range 1-4
    hitTimer = 60;
}

void player::DrawPlayer()
{
    // count down hit timer; when it expires go back to normal frame
    if (hitTimer > 0)
        hitTimer--;
    else
        imageIndex = 0;

    al_draw_bitmap(images[imageIndex], x, y, 0);
}

void player::MoveUp()
{
    y -= speed;
    if (y < 0) y = 0;
}

void player::MoveDown(int HEIGHT)
{
    y += speed;
    // fix: clamp so Kirby can't go off the bottom
    if (y + boundy > HEIGHT)
        y = HEIGHT - boundy;
}

void player::MoveLeft()
{
    x -= speed;
    if (x < 0) x = 0;
}

void player::MoveRight()
{
    x += speed;
    if (x > 300) x = 300;
}