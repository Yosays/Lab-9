#ifndef PLAYERH
#define PLAYERH

#include <allegro5/allegro.h>

class player
{
public:
    player(int HEIGHT);
    ~player();
    void DrawPlayer();
    void MoveUp();
    void MoveDown(int HEIGHT);
    void MoveLeft();
    void MoveRight();
    int  getBoundX() { return boundx; }
    int  getBoundY() { return boundy; }
    int  getX() { return x; }
    int  getY() { return y; }
    int  getLives() { return lives; }
    int  getScore() { return score; }
    void addScore() { score++; }
    void removeLife();
    bool isDead() { return lives <= 0; }

private:
    int x, y;
    int lives;
    int speed;
    int boundx, boundy;
    int score;

    // damage animation
    ALLEGRO_BITMAP* images[5];   // kirby0 - kirby4
    int  imageIndex;             // which frame to draw
    int  hitTimer;               // counts down after a hit
};

#endif