#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "player.h"
#include "ghost.h"
#include "Arrow.h"
#include <cstdio>

int main(void)
{
    const int WIDTH = 800;
    const int HEIGHT = 400;
    const int NUM_ARROWS = 5;
    const int NUM_GHOSTS = 10;
    const int FPS = 60;

    enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };
    bool keys[5] = { false, false, false, false, false };

    bool done = false;
    bool redraw = true;

    // ---- init ----
    al_init();
    al_install_keyboard();
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    ALLEGRO_DISPLAY* display = al_create_display(WIDTH, HEIGHT);
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
    ALLEGRO_FONT* font = al_create_builtin_font();

    al_set_window_title(display, "Lab 9 - Kirby Shooter");

    srand(time(NULL));

    // ---- objects ----
    player myPlayer(HEIGHT);
    Arrow  Arrows[NUM_ARROWS];
    ghost  ghosts[NUM_GHOSTS];

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));

    al_start_timer(timer);

    // ---- main loop ----
    while (!done)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;

            if (keys[UP])    myPlayer.MoveUp();
            if (keys[DOWN])  myPlayer.MoveDown(HEIGHT);
            if (keys[LEFT])  myPlayer.MoveLeft();
            if (keys[RIGHT]) myPlayer.MoveRight();

            for (int i = 0; i < NUM_ARROWS; i++)
                Arrows[i].UpdateArrow(WIDTH);
            for (int i = 0; i < NUM_GHOSTS; i++)
                ghosts[i].Startghost(WIDTH, HEIGHT);
            for (int i = 0; i < NUM_GHOSTS; i++)
                ghosts[i].Updateghost();
            for (int i = 0; i < NUM_ARROWS; i++)
                Arrows[i].CollideArrow(ghosts, NUM_GHOSTS, myPlayer);
            for (int i = 0; i < NUM_GHOSTS; i++)
                ghosts[i].Collideghost(myPlayer);

            // ---- game over check ----
            if (myPlayer.isDead())
            {
                // show game over screen for 5 seconds
                al_clear_to_color(al_map_rgb(0, 0, 0));

                char stats[128];
                sprintf_s(stats, "GAME OVER!  Lives: 0   Ghosts Killed: %d", myPlayer.getScore());
                al_draw_text(font, al_map_rgb(255, 50, 50),
                    WIDTH / 2, HEIGHT / 2 - 10,
                    ALLEGRO_ALIGN_CENTRE, stats);
                al_draw_text(font, al_map_rgb(255, 255, 255),
                    WIDTH / 2, HEIGHT / 2 + 20,
                    ALLEGRO_ALIGN_CENTRE, "Closing in 5 seconds...");

                al_flip_display();
                al_rest(5.0);
                done = true;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            done = true;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE: done = true; break;
            case ALLEGRO_KEY_UP:     keys[UP] = true; break;
            case ALLEGRO_KEY_DOWN:   keys[DOWN] = true; break;
            case ALLEGRO_KEY_LEFT:   keys[LEFT] = true; break;
            case ALLEGRO_KEY_RIGHT:  keys[RIGHT] = true; break;
            case ALLEGRO_KEY_SPACE:
                keys[SPACE] = true;
                for (int i = 0; i < NUM_ARROWS; i++)
                    Arrows[i].FireArrow(myPlayer);
                break;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE: done = true; break;
            case ALLEGRO_KEY_UP:     keys[UP] = false; break;
            case ALLEGRO_KEY_DOWN:   keys[DOWN] = false; break;
            case ALLEGRO_KEY_LEFT:   keys[LEFT] = false; break;
            case ALLEGRO_KEY_RIGHT:  keys[RIGHT] = false; break;
            case ALLEGRO_KEY_SPACE:  keys[SPACE] = false; break;
            }
        }

        // ---- draw ----
        if (redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;

            al_clear_to_color(al_map_rgb(0, 0, 0));

            myPlayer.DrawPlayer();

            for (int i = 0; i < NUM_ARROWS; i++)
                Arrows[i].DrawArrow();
            for (int i = 0; i < NUM_GHOSTS; i++)
                ghosts[i].Drawghost();

            // ---- HUD ----
            char livesText[32];
            char scoreText[32];
            sprintf_s(livesText, "Lives: %d", myPlayer.getLives());
            sprintf_s(scoreText, "Ghosts Killed: %d", myPlayer.getScore());

            al_draw_text(font, al_map_rgb(255, 255, 0), 10, 10, 0, livesText);
            al_draw_text(font, al_map_rgb(255, 255, 0), 10, 25, 0, scoreText);

            al_flip_display();
        }
    }

    // ---- cleanup ----
    al_destroy_font(font);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_display(display);

    return 0;
}