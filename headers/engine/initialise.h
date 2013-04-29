#ifndef __blackhole_initialise_h__
#define __blackhole_initialise_h__

#define ALLEGRO_STATICLINK
#include "allegro5/allegro.h"
#include "allegro5/allegro_memfile.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"

#ifdef _WIN32
  #include <windows.h>
  #include "allegro5/allegro_windows.h"
  #define BH_ADD_RESOURCE(path, nick1, nick2) \
    extern unsigned char binary_ ## path ## _start; \
    extern int binary_ ## path ## _size; \
    void *nick1 = & binary_ ## path ## _start;\
    int nick2 = (int) & binary_ ## path ## _size;
#else 
  #define BH_ADD_RESOURCE(path, nick1, nick2) \
    extern unsigned char _binary_ ## path ## _start; \
    extern int _binary_ ## path ## _size; \
    void *nick1 = &_binary_ ## path ## _start; \
    int nick2 = (int) & _binary_ ## path ## _size;
#endif

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
  //  ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *booster_sample, *blackhole_noise_sample;
    ALLEGRO_SAMPLE_ID noise_id;

    float get_FPS();
    float get_width();
    float get_height();
    void destroy();
};

#endif
