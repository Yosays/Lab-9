#ifndef ARROWH
#define ARROWH
#include "player.h"
#include "ghost.h"

class Arrow
{
public:
    Arrow();
    ~Arrow();
    void DrawArrow();
    void FireArrow(player& Player);
    void UpdateArrow(int WIDTH);
    void CollideArrow(ghost ghosts[], int cSize, player& Player);

private:
    int x, y;
    bool live;
    int speed;
    ALLEGRO_BITMAP* image;
};

#endif