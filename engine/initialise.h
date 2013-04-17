#ifndef __blackhole_initialise_h__
#define __blackhole_initialise_h__

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class Game_Reqs {
  private:
    float FPS;
    float screen_w;
    float screen_h;

  public: 
    Game_Reqs(float FPS, float width, float height);
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_TIMER *timer;
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *booster, *noise;
    ALLEGRO_SAMPLE_ID noise_id;

    float get_FPS();
    float get_width();
    float get_height();
    void destroy();
};

#endif
