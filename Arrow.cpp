#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "Arrow.h"

Arrow::Arrow()
{
    speed = 10;
    live = false;
    image = al_load_bitmap("arrow.png");
}

Arrow::~Arrow()
{
    al_destroy_bitmap(image);
}

void Arrow::DrawArrow()
{
    if (live)
        al_draw_rotated_bitmap(image,
            al_get_bitmap_width(image) / 2,
            al_get_bitmap_height(image) / 2,
            x, y, 90, 0);
}

void Arrow::FireArrow(player& Player)
{
    if (!live)
    {
        x = Player.getX();
        y = Player.getY();
        live = true;
    }
}

void Arrow::UpdateArrow(int WIDTH)
{
    if (live)
    {
        x += speed;
        if (x > WIDTH)
            live = false;
    }
}

// now accepts player ref so kills increment score
void Arrow::CollideArrow(ghost ghosts[], int cSize, player& Player)
{
    if (live)
    {
        for (int j = 0; j < cSize; j++)
        {
            if (ghosts[j].getLive())
            {
                if (x > (ghosts[j].getX() - ghosts[j].getBoundX()) &&
                    x < (ghosts[j].getX() + ghosts[j].getBoundX()) &&
                    y >(ghosts[j].getY() - ghosts[j].getBoundY()) &&
                    y < (ghosts[j].getY() + ghosts[j].getBoundY()))
                {
                    live = false;
                    ghosts[j].setLive(false);
                    Player.addScore();   // count the kill
                }
            }
        }
    }
}