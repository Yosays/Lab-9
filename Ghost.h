#ifndef GHOSTH
#define GHOSTH
#include "player.h"

class ghost
{
public:
    ghost();
    ~ghost();
    void Drawghost();
    void Startghost(int WIDTH, int HEIGHT);
    void Updateghost();
    void Collideghost(player& Player);
    int  getBoundX() { return boundx; }
    int  getBoundY() { return boundy; }
    int  getX() { return x; }
    int  getY() { return y; }
    bool getLive() { return live; }
    void setLive(bool l) { live = l; }

private:
    int x, y;
    bool live;
    int speed;
    int boundx, boundy;
    ALLEGRO_BITMAP* image;
};

#endif