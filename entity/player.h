#ifndef __player_h__
#define __player_h__

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <math.h>
#include "blackhole.h"
#include "../engine/error.h"
#include "../engine/initialise.h"

class Player {
  private:
    float r, theta;
    float vel_r, vel_theta;
    float force_r, force_theta;
    int fuel;
    int boost_fuel;
    int wait_for_boost;
    
    ALLEGRO_BITMAP *sprite;
    ALLEGRO_BITMAP *sprite_animations[32][5];
    ALLEGRO_FONT *font;

    int state;
    int anim_state;
    float display_w, display_h;
    float sprite_w, sprite_h;

  public:
    Player(Game_Reqs *reqs, int radius);
    void draw();
    void left(bool move);
    void right(bool move);
    void up(bool move);
    void down(bool move);
    void destroy();
    float get_angle();
    float get_radial_position();
};

#endif
